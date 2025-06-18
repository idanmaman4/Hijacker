#include "InjectorCommnadLineParser.hpp"

InjectorCommnadLineParser::InjectorCommnadLineParser(const std::wstring& command_line) : BaseParser<CommandLineArgs>(command_line)
{

}

CommandLineArgs InjectorCommnadLineParser::get_arguments_parsing(ArgumentsList& arguments_raw) const
{
    return { std::move(arguments_raw[static_cast<int>(m_Arguments::ProgramName)]), std::move(arguments_raw[static_cast<int>(m_Arguments::InjecteePath)]) };
}

bool InjectorCommnadLineParser::check_arguments_correctness(ArgumentsList& arguments_raw) const
{
    return arguments_raw.size() == static_cast<int>(m_Arguments::ArgumentsNum);
}

