//
// Created by 35691 on 7/14/2023.
//

#ifndef RUNNER_COMMON_H
#define RUNNER_COMMON_H

#include <string>
#include <map>

namespace app
{
namespace fonts
{
static const std::string FounderFont = "fonts/SourceHanSansCN-Normal.otf";
}
namespace lan
{

enum class Language
{
    Chinese,
    English,

};

constexpr Language getDefaultLanguage()
{
    return Language(0);
}

static const std::map<Language, std::string> LanguageMap = {
    {Language::Chinese, "language/lan_cn.json"},
    {Language::English, "language/lan_en.json"},
};

}
};      // namespace app

#endif  // RUNNER_COMMON_H
