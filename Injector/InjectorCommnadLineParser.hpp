#pragma once

#include "Defines.hpp"
#include "GenericException.hpp"
#include "WinApiException.hpp"
#include "BaseParser.hpp"

#include <string>
#include <vector>
#include <filesystem>

struct CommandLineArgs {
		std::filesystem::path program_name;
		std::filesystem::path injectee_name;
};

class InjectorCommnadLineParser final : public BaseParser<CommandLineArgs>
{
public:
	explicit InjectorCommnadLineParser(const std::wstring& command_line);

	~InjectorCommnadLineParser() = default;

	InjectorCommnadLineParser(InjectorCommnadLineParser&) = delete;
	InjectorCommnadLineParser(InjectorCommnadLineParser&&) = delete;
	InjectorCommnadLineParser& operator=(InjectorCommnadLineParser&) = delete;
	InjectorCommnadLineParser& operator=(InjectorCommnadLineParser&&) = delete;

private:
	enum Arguments {
		ProgramName = 0,
		InjecteePath,
		ArgumentsNum

	};

	NO_DISCARD CommandLineArgs get_parsed_arguments(ArgumentsList& arguments_raw) const override;
	NO_DISCARD bool check_arguments_correctness(ArgumentsList& arguments_raw) const override;
};
