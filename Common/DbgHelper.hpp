#pragma once

#include "UserOutput.hpp"

#include <string>

class DbgHelper final
{
public:
#ifdef _DEBUG
	static constexpr bool is_mode_debug = true;
#else
	static constexpr bool is_mode_debug = false;
#endif 
	static void show_dbg_message(const std::wstring& message);

	DbgHelper() = delete;
	~DbgHelper() = delete;
	DbgHelper(DbgHelper&) = delete;
	DbgHelper(DbgHelper&&) = delete;
	DbgHelper& operator=(DbgHelper&) = delete;
	DbgHelper& operator=(DbgHelper&&) = delete;
};

