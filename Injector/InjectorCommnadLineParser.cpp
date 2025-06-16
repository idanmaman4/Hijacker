#include "InjectorCommnadLineParser.hpp"

InjectorCommnadLineParser::InjectorCommnadLineParser(const std::wstring& command_line) : BaseParser<CommandLineArgs>(command_line)
{

}

CommandLineArgs InjectorCommnadLineParser::get_args() const
{
    ArgumentsList arugments = get_argument_list();
    if (arugments.size() != static_cast<int>(Arguments::ArgumentsNum)) {
        throw GenericException(std::format("Excpected {} args", static_cast<int>(Arguments::ArgumentsNum)));
    }

    return CommandLineArgs(arugments[static_cast<int>(Arguments::ProgramName)], arugments[static_cast<int>(Arguments::InjecteePath)]);
}

