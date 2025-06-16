#pragma once

#include "SmartMessageBox.hpp"

#include <Windows.h>
#include <string>


class DbgHelper final
{
public:
	DbgHelper() = delete;

#ifdef _DEBUG
	static constexpr bool is_mode_debug = true;
#else
	static constexpr bool is_mode_debug = false;
#endif 
	static void show_dbg_message(const std::string& message);

};

