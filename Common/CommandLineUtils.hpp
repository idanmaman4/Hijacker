#pragma once

#include "DefineTypes.hpp"
#include <string>
#include <regex>
#include <sstream>
#include <ranges>
#include <format>

namespace CommandLineUtils
{
	std::wstring escape_string_for_command_line(const std::wstring& string_to_escape);
	std::wstring create_command_line(const ArgumentsList& arguments);
};
