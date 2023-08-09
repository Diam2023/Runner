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
        CCLOGINFO("%s", str_.c_str());
    }

    std::string data = FileUtils::getInstance()->getStringFromFile(lanFile);
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
