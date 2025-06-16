#pragma once

#include "defines.hpp"
#include "GenericException.hpp"
#include "WinApiGeneralException.hpp"

#include <string>
#include <vector>
#include <filesystem>
#include <Windows.h>


// [CR] Remove New Lines!
using ArgsList = std::vector<std::wstring>;

class InjectorCommnadLineParser final
{
public:
	
	enum class Arguments {
		ProgramName = 0,
		InjecteePath,
		ArgumentsNum
	
	};
	// [CR] Conventions - PascalCase Type names
	struct command_line_args {
		std::filesystem::path program_name;
		std::filesystem::path injectee_name;
	};

	explicit InjectorCommnadLineParser(const std::wstring& command_line);
	NODISCARD command_line_args get_args() const;

	~InjectorCommnadLineParser() = default;

	InjectorCommnadLineParser(InjectorCommnadLineParser&) = delete;
	InjectorCommnadLineParser(InjectorCommnadLineParser&&) = delete;
	InjectorCommnadLineParser& operator= (InjectorCommnadLineParser&) = delete;
	InjectorCommnadLineParser& operator= (InjectorCommnadLineParser&&) = delete;

private:
	// [CR] Naming - parse_arguments_string
	static NODISCARD ArgsList parse_args(const std::wstring& command_line);

	std::wstring m_command_line;
};

