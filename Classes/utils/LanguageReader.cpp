//
// Created by 35691 on 7/14/2023.
//

#include "LanguageReader.h"

#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stream.h"
#include "json/istreamwrapper.h"

#include <fstream>
#include <scripting/deprecated/CCDeprecated.h>
#include <scripting/deprecated/CCDictionary.h>

using namespace std;
using namespace cocos2d;
using namespace rapidjson;

char* FontToUTF8(const char* font)
{
    int len = MultiByteToWideChar(CP_ACP, 0, font, -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len + 1];
    memset(wstr, 0, len + 1);
    MultiByteToWideChar(CP_ACP, 0, font, -1, wstr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* str = new char[len + 1];
    memset(str, 0, len + 1);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
    if (wstr)
        delete[] wstr;
    return str;
}

void LanguageReader::init(app::lan::Language lan)
{
    nowLanguage = lan;
    const auto& lanFile = app::lan::LanguageMap.at(lan);
    auto fileExistResult = FileUtils::getInstance()->isFileExist(lanFile);

    CCASSERT(fileExistResult, "Cannot Find Language File!!!");

    auto ful = FileUtils::getInstance()->fullPathForFilename(lanFile);

    ifstream stream(ful);
    if (!stream)
    {
        CCLOGWARN("Error Read");
    }
    else
    {
        std::string str_((std::istreambuf_iterator<char>(stream)),
                         std::istreambuf_iterator<char>());
        CCLOGINFO(str_.c_str());
    }

    std::string data = FileUtils::getInstance()->getStringFromFile(lanFile);
    const char* str = FontToUTF8(data.c_str());

    this->document.Parse(data.c_str());
    CCASSERT(this->document.IsObject(), "Language File syntax Error!!!");
}

LanguageReader::LanguageReader() : nowLanguage(app::lan::getDefaultLanguage())
{
    this->init(nowLanguage);
}

std::string LanguageReader::getMenuValue(const string& name)
{
    this->document["Menu"].IsObject();
    return "";
}

std::string LanguageReader::getAppName()
{
    if (!this->document["AppName"].IsString())
    {
        CCLOGERROR("Error Read AppName!!");
        return "";
    }

    return this->document["AppName"].GetString();
}
