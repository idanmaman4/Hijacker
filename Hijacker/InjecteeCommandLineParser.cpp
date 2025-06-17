#include "InjecteeCommandLineParser.hpp"

InjecteeCommandLineParser::InjecteeCommandLineParser(const std::wstring& command_line) : BaseParser<InjecteeCommandLineArgs>(command_line)
{
}

NODISCARD InjecteeCommandLineArgs InjecteeCommandLineParser::get_args() const
{
	ArgumentsList arguments = get_argument_list();
	if (arguments.size() < static_cast<int>(Arguments::MinimumArgumentsCount)) {
		throw GenericException("There is too less arguments!!");
	}
	std::filesystem::path program_name = arguments[static_cast<int>(Arguments::ProgramName)];

	return {std::move(program_name), std::move(arguments)}; 
}
