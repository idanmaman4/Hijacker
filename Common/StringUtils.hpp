#pragma once

#include "DefineTypes.hpp"
#include <string>
#include <regex>
#include <sstream>
#include <ranges>
#include <format>
// [CR] Naming - CommandLineUtils? 
namespace StringUtils
{
	// [CR] Naming - command_line
	std::wstring escape_string_for_commandline(const std::wstring& string_to_escape);
	std::wstring create_commandline(const ArgumentsList& arguments);
};
