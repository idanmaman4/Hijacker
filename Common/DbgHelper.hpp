#pragma once

#include "UserOutput.hpp"

#include <string>

//CR: [naming] This class smells like a Windows util. to make it feel like a Maman util name it DebugHelper
class DbgHelper final
{
public:
#ifdef _DEBUG
	//CR: [naming] Prefer is_debug_mode
	static constexpr bool is_mode_debug = true;
#else
	static constexpr bool is_mode_debug = false;
#endif 
	//CR: [naming] Dont use words like dbg
	static void show_dbg_message(const std::wstring& message);

	DbgHelper() = delete;
	~DbgHelper() = delete;
	DbgHelper(DbgHelper&) = delete;
	DbgHelper(DbgHelper&&) = delete;
	DbgHelper& operator=(DbgHelper&) = delete;
	DbgHelper& operator=(DbgHelper&&) = delete;
};

