#pragma once

#include "defines.hpp"
#include "WinApiGeneralException.hpp"

#include <string>
#include <vector>
#include <format>
#include <ranges>
#include <regex>
#include <sstr>


class Process final
{
public:
	void wait(size_t time = INFINITE);
	~Process();
	Process(Process&) = default;
	Process(Process&& ) = default;
	static Process create_process_debug(const std::wstring& process_name, const ArgumentsList& arguments); 

	Process& operator=(Process& ) = delete;
	Process operator= (Process&& ) = delete;

private:
	static void stop_debugging(DWORD process_id);
	explicit Process(HANDLE handle_to_process );
	HANDLE m_handle;
};

