#pragma once

#include "defines.hpp"
#include "WinApiGeneralException.hpp"

#include <string>
#include <vector>
#include <format>
#include <ranges>
#include <regex>
#include <sstream>


class Process final
{
public:
	Process(Process&& );
	void wait(size_t time = INFINITE);
	~Process();
	static NODISCARD Process create_process_debug(const std::wstring& process_name, const ArgumentsList& arguments); 
	Process& operator=(Process& ) = delete;
	Process& operator= (Process&& ) = delete;
	Process(Process&) = delete;

private:
	explicit Process(HANDLE handle_to_process );
	static void stop_debugging(DWORD process_id);
	static std::wstring escape_string_for_commandline(const std::wstring& string_to_escape);

	HANDLE m_handle;
};

