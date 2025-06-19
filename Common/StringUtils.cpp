#include "StringUtils.hpp"

std::wstring StringUtils::escape_string_for_commandline(const std::wstring& string_to_escape)
{
    static const std::wregex pattern(L"\"");
    static const std::wstring replacement(L"\\\"");

    return std::format(L"\"{}\"",std::regex_replace(string_to_escape, pattern, replacement));
}

std::wstring StringUtils::create_commandline(const ArgumentsList& arguments)
{
    std::wstringstream command_line_string;
    for (const auto& argument : arguments | std::views::transform(escape_string_for_commandline) | std::views::join_with(' ')) {
        command_line_string << argument;
    }

    return std::move(command_line_string.str());
}
