#pragma once

#include "Defines.hpp"
#include "DefineWinApi.hpp"
#include "WinApiException.hpp"
#include "Handle.hpp"
#include "CommandLineUtils.hpp"

class DebuggedProcess final
{
public:
	DebuggedProcess(const std::wstring& process_name, const ArgumentsList& arguments);

	void stop_debugging();
	void wait(size_t time = INFINITE);
	NO_DISCARD size_t get_process_id();

	~DebuggedProcess() = default;

	DebuggedProcess(DebuggedProcess&& DebuggedProcess) = delete;
	DebuggedProcess& operator=(DebuggedProcess&) = delete;
	DebuggedProcess& operator=(DebuggedProcess&&) = delete;
	DebuggedProcess(DebuggedProcess&) = delete;

private:
	static Handle create_debugged_process(const std::wstring& DebuggedProcess_name, const ArgumentsList& arguments); 

	Handle m_handle;
};
