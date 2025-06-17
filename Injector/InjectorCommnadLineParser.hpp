#pragma once

#include "defines.hpp"
#include "GenericException.hpp"
#include "WinApiGeneralException.hpp"
#include "BaseParser.hpp"

#include <string>
#include <vector>
#include <filesystem>


struct CommandLineArgs {//ADT : just holds data without any logic!
		std::filesystem::path program_name;
		std::filesystem::path injectee_name;
};

class InjectorCommnadLineParser final : public BaseParser<CommandLineArgs>
{
public:
	enum class Arguments {
		ProgramName=0,
		InjecteePath,
		ArgumentsNum
	
	};

	explicit InjectorCommnadLineParser(const std::wstring& command_line);
	~InjectorCommnadLineParser() = default;

	InjectorCommnadLineParser(InjectorCommnadLineParser&) = delete;
	InjectorCommnadLineParser(InjectorCommnadLineParser&&) = delete;
	InjectorCommnadLineParser& operator= (InjectorCommnadLineParser&) = delete;
	InjectorCommnadLineParser& operator= (InjectorCommnadLineParser&&) = delete;

private:
	NODISCARD CommandLineArgs get_arguments_parsing(ArgumentsList& arguments_raw) const override;
	NODISCARD bool check_arguments_correction(ArgumentsList& arguments_raw) const override;
};

