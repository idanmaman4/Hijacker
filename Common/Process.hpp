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
	void stop_debugging();
	void wait(size_t time = INFINITE);
	NODISCARD unsigned int get_process_id();
	~Process();
	static NODISCARD Process create_debugged_process(const std::wstring& process_name, const ArgumentsList& arguments); 

	Process& operator=(Process& ) = delete;
	Process& operator= (Process&& ) = delete;
	Process(Process&) = delete;

private:
	explicit Process(HANDLE handle_to_process );
	static std::wstring escape_string_for_commandline(const std::wstring& string_to_escape);
	static std::wstring create_commandline(const ArgumentsList& arguments);
	HANDLE m_handle;
};

