#pragma once

#include "Defines.hpp"
#include "DefineWinApi.hpp"
#include "WinApiException.hpp"
#include "Handle.hpp"
#include "StringUtils.hpp"
// [CR] Naming - DebuggedProcess?
class CreatedProcess final
{
public:
	CreatedProcess(const std::wstring& process_name, const ArgumentsList& arguments);

	~CreatedProcess() = default;

	void stop_debugging();
	void wait(size_t time = INFINITE);
	// [CR] Implementation - unsigned int?
	NO_DISCARD unsigned int get_process_id();
	
	CreatedProcess(CreatedProcess&& CreatedProcess) = delete;
	CreatedProcess& operator=(CreatedProcess&) = delete;
	CreatedProcess& operator=(CreatedProcess&&) = delete;
	CreatedProcess(CreatedProcess&) = delete;

private:
	static Handle create_debugged_process(const std::wstring& CreatedProcess_name, const ArgumentsList& arguments); 

	Handle m_handle;
};
