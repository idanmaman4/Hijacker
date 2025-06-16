#include "InjectorCommnadLineParser.hpp"


InjectorCommnadLineParser::InjectorCommnadLineParser(const std::wstring& command_line) : m_command_line(command_line)
{
}

InjectorCommnadLineParser::command_line_args InjectorCommnadLineParser::get_args() const
{
    ArgsList args_list = parse_args(m_command_line);
    if (args_list.size() != static_cast<int>(Arguments::ArgumentsNum)) {
        throw GenericException(std::format("Excpected {} args", static_cast<int>(Arguments::ArgumentsNum)));
    }

    return command_line_args(args_list[0],args_list[1]);
}

ArgsList InjectorCommnadLineParser::parse_args(const std::wstring& command_line)
{
    int argc;
    LPWSTR* args = CommandLineToArgvW(command_line.c_str(), &argc );
    if (args == NULL) {
        throw WinApiGeneralException("Unable To parse command Line!");
    }
    ArgsList args_parsed(args , args + argc);
    LocalFree(args);
    return args_parsed;
}
