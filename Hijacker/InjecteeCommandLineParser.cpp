#include "InjecteeCommandLineParser.hpp"

InjecteeCommandLineParser::InjecteeCommandLineParser(const std::wstring& command_line) : BaseParser<InjecteeCommandLineArgs>(command_line)
{
}

InjecteeCommandLineArgs InjecteeCommandLineParser::get_arguments_parsing(ArgumentsList& arguments_raw) const
{
	std::filesystem::path program_name = arguments_raw[static_cast<int>(Arguments::ProgramName)];

	return {std::move(program_name), std::move(arguments_raw)};
}

bool InjecteeCommandLineParser::check_arguments_correction(ArgumentsList& arguments_raw) const
{
	return arguments_raw.size() >= static_cast<int>(Arguments::MinimumArgumentsCount);
}
