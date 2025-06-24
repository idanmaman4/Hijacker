#include "DebuggedProcess.hpp"

DebuggedProcess::DebuggedProcess(const std::wstring& process_name, const ArgumentsList& arguments) : 
    m_handle(create_debugged_process(process_name, arguments))
{

}

void DebuggedProcess::stop_debugging()
{
    if (!DebugActiveProcessStop(static_cast<DWORD>(get_process_id()))) {
        throw WinApiException(L"Can't detach from DebuggedProcess!");
    }
}

void DebuggedProcess::wait(size_t time)
{
    DWORD res = WaitForSingleObject(m_handle.get_raw_handle(), static_cast<DWORD>(time));
    if (res == WAIT_FAILED) {
        throw WinApiException(L"Wait has been failed!");
    }
    if (res == WAIT_ABANDONED) {
        throw WinApiException(L"TimeOUT!");
    }
}

NO_DISCARD size_t DebuggedProcess::get_process_id()
{
    DWORD process_id = GetProcessId(m_handle.get_raw_handle());
    if (!process_id) {
        throw WinApiException(L"Can't get DebuggedProcess-id from the current handle!");
    }

    return process_id;
}

Handle DebuggedProcess::create_debugged_process(const std::wstring& DebuggedProcess_name, const ArgumentsList& arguments)
{
    STARTUPINFO startup_information{ 0 };
    PROCESS_INFORMATION process_information{ 0 };
    startup_information.cb = sizeof(startup_information);  
    std::wstring commandline = CommandLineUtils::create_command_line(arguments);
    static constexpr LPSECURITY_ATTRIBUTES DEFAULT_SECURITY_ATTRIBUTES = NULL;
    static constexpr BOOL DEFAULT_HANDLE_INHERITANCE = NULL;
    static constexpr BOOL DEFAULT_DW_TYPE = NORMAL_PRIORITY_CLASS | DEBUG_PROCESS | DEBUG_ONLY_THIS_PROCESS;
    static constexpr  LPVOID DEFAULT_INHERIT_ENVIROMENT = NULL;
    static constexpr LPCWSTR DEFAULT_CURNRENT_DIRECTORY = NULL;
    BOOL status = CreateProcessW(DebuggedProcess_name.c_str(),
        const_cast<LPWSTR>(commandline.c_str()),
        DEFAULT_SECURITY_ATTRIBUTES,
        DEFAULT_SECURITY_ATTRIBUTES,
        DEFAULT_HANDLE_INHERITANCE,
        DEFAULT_DW_TYPE,
        DEFAULT_INHERIT_ENVIROMENT,
        DEFAULT_CURNRENT_DIRECTORY,
        &startup_information,
        &process_information
    );
    if (!status) {
        throw WinApiException(L"Can't Create DebuggedProcess");
    }
    Handle thread_handle(process_information.hThread);

    return Handle{ process_information.hProcess };
}
