#pragma once

#include "defines.hpp"
#include "GenericException.hpp"
#include "WinApiGeneralException.hpp"
#include "BaseParser.hpp"
#include "Process.hpp"

#include <string>
#include <vector>
#include <filesystem>

using ArgumentsList = std::vector<std::wstring>;

struct InjecteeCommandLineArgs {//ADT : just holds data without any logic!
		std::filesystem::path program_name;
		ArgumentsList arguments;
};

class InjecteeCommandLineParser final : public BaseParser<InjecteeCommandLineArgs>
{
public:
	
	enum class Arguments {
		ProgramName=0,
		MinimumArgumentsCount,	
	};

	explicit InjecteeCommandLineParser(const std::wstring& command_line);
	~InjecteeCommandLineParser() = default;

	InjecteeCommandLineParser(InjecteeCommandLineParser&) = delete;
	InjecteeCommandLineParser(InjecteeCommandLineParser&&) = delete;
	InjecteeCommandLineParser& operator= (InjecteeCommandLineParser&) = delete;
	InjecteeCommandLineParser& operator= (InjecteeCommandLineParser&&) = delete;

private:
	NODISCARD InjecteeCommandLineArgs get_arguments_parsing(ArgumentsList& arguments_raw) const override;
	NODISCARD bool check_arguments_correction(ArgumentsList& arguments_raw) const override;
};

