#pragma once

#include "Defines.hpp"
#include "GenericException.hpp"
#include "WinApiException.hpp"
#include "BaseParser.hpp"

#include <string>
#include <vector>
#include <filesystem>

struct InjecteeCommandLineArgs {
	std::filesystem::path program_name;
	ArgumentsList arguments;
};

class InjecteeCommandLineParser final : public BaseParser<InjecteeCommandLineArgs>
{
public:
	explicit InjecteeCommandLineParser(const std::wstring& command_line);

	~InjecteeCommandLineParser() = default;

	InjecteeCommandLineParser(InjecteeCommandLineParser&) = delete;
	InjecteeCommandLineParser(InjecteeCommandLineParser&&) = delete;
	InjecteeCommandLineParser& operator= (InjecteeCommandLineParser&) = delete;
	InjecteeCommandLineParser& operator= (InjecteeCommandLineParser&&) = delete;

private:
	enum Arguments {
		ProgramName = 0,
		MinimumArgumentsCount,
	};

	NO_DISCARD InjecteeCommandLineArgs get_parsed_arguments(ArgumentsList& arguments_raw) const override;
	NO_DISCARD bool check_arguments_correctness(ArgumentsList& arguments_raw) const override;
};
