#pragma once

#include "UserOutput.hpp"

#include <string>

namespace DebugHelper 
{
#ifdef _DEBUG
	static constexpr bool is_debug_mode = true;
#else
	static constexpr bool is_debug_mode = false;
#endif 

	void show_debug_message(const std::wstring& message);
};
