//
// Created by 35691 on 7/14/2023.
//

#pragma once

#include "common.h"
#include "json/document.h"

class LanguageReader
{
  private:

  protected:
    rapidjson::Document document;

  public:
    rapidjson::Document& getDocument()
    {
        return document;
    }
  protected:
    app::lan::Language nowLanguage;

  public:
    LanguageReader();
    ~LanguageReader() = default;

    void init(app::lan::Language lan);

    static LanguageReader& getInstance()
    {
        static LanguageReader lr;
        return lr;
    }

    std::string getAppName();

    std::string getMenuValue(const std::string& name);
    std::string getGameValue(const std::string& name);
    std::string getMenuItemValue(const std::string& name);
    std::string getSettingValue(const std::string& name);
};
