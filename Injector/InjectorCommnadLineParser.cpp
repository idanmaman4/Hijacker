#include "InjectorCommnadLineParser.hpp"

InjectorCommnadLineParser::InjectorCommnadLineParser(const std::wstring& command_line) : BaseParser<CommandLineArgs>(command_line)
{

}

CommandLineArgs InjectorCommnadLineParser::get_parsed_arguments(ArgumentsList& arguments_raw) const
{
    // [CR] Implementation - remove the casts
    return { std::move(arguments_raw[static_cast<int>(ProgramName)]), std::move(arguments_raw[static_cast<int>(InjecteePath)]) };
}

bool InjectorCommnadLineParser::check_arguments_correctness(ArgumentsList& arguments_raw) const
{
    return arguments_raw.size() == static_cast<int>(ArgumentsNum);
}
