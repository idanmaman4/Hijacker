#include "InjectorCommnadLineParser.hpp"

// [CR] Remove New Line
InjectorCommnadLineParser::InjectorCommnadLineParser(const std::wstring& command_line) : m_command_line(command_line)
{
}

InjectorCommnadLineParser::command_line_args InjectorCommnadLineParser::get_args() const
{
    // [CR] Naming - arugments
    ArgsList args_list = parse_args(m_command_line);
    if (args_list.size() != static_cast<int>(Arguments::ArgumentsNum)) {
        throw GenericException(std::format("Excpected {} args", static_cast<int>(Arguments::ArgumentsNum)));
    }
    // [CR] Conventions - space after comma
    // [CR] Magic - use the enum YOU DEFINED
    return command_line_args(args_list[0],args_list[1]);
}

ArgsList InjectorCommnadLineParser::parse_args(const std::wstring& command_line)
{
    // [CR] Naming - nubmer_of_arguments
    int argc;
    // [CR] Naming - arguments
    LPWSTR* args = CommandLineToArgvW(command_line.c_str(), &argc );
    if (args == NULL) {
        throw WinApiGeneralException("Unable To parse command Line!");
    }
    ArgsList args_parsed(args , args + argc);
    // [CR] Implementation - Manual resource management! Where i RAII?
    LocalFree(args);
    return args_parsed;
}
