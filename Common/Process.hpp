#pragma once

#include "defines.hpp"
#include "WinApiGeneralException.hpp"

#include <string>
#include <vector>
#include <format>
#include <ranges>
#include <regex>
#include <sstream>

//CR: [design] Your design is a bit complicated relative to what I expect of a Process class,
//             specifically the fact that you can only create a process using a static function.
//             Constructing a process using a ctor that accepts a name param is simpler.
class Process final
{
public:
	//CR: [misc] space?
	//CR: [misc] No unamed params
	Process(Process&& );
	//CR: [conventions] functions order
	void stop_debugging();
	void wait(size_t time = INFINITE);
	NODISCARD unsigned int get_process_id();
	~Process();
	static NODISCARD Process create_debugged_process(const std::wstring& process_name, const ArgumentsList& arguments); 

	Process& operator=(Process& ) = delete;
	Process& operator= (Process&& ) = delete;
	Process(Process&) = delete;

private:
	//CR: [misc] remove space
	explicit Process(HANDLE handle_to_process );
	//CR: [naming] Prefer command_line
	//CR: [misc] This string functions are utils that can be outside of here.
	static std::wstring escape_string_for_commandline(const std::wstring& string_to_escape);
	static std::wstring create_commandline(const ArgumentsList& arguments);
	//CR: [misc] newline here
	HANDLE m_handle;
};

