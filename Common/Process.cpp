#include "Process.hpp"

std::wstring Process::escape_string_for_commandline(const std::wstring& string_to_escape){
    static const std::wregex pattern(L"\"");
    static const std::wstring replacement(L"\\\"");

    return std::format(L"\"{}\"",std::regex_replace(string_to_escape, pattern, replacement));
}

std::wstring Process::create_commandline(const ArgumentsList& arguments)
{
    std::wstringstream command_line_string;
    for (const auto& argument  : arguments | std::views::transform(escape_string_for_commandline) | std::views::join_with(' ')) {
        command_line_string << argument;
    }

    return std::move(command_line_string.str());
}

Process::~Process()
{
    try {
        if (m_handle != INVALID_HANDLE_VALUE) {
            CloseHandle(m_handle);
        }
    }
    catch (...) {}
}

void Process::stop_debugging()
{
    if (!DebugActiveProcessStop(get_process_id())) {
        throw WinApiGeneralException(L"Can't detach from process!");
    }
}

void Process::wait(size_t time)
{
    DWORD res = WaitForSingleObject(m_handle,static_cast<DWORD>(time));
    if (res == WAIT_FAILED) {
        throw WinApiGeneralException(L"Wait has been failed!");
    }
    if (res == WAIT_ABANDONED) {
        throw WinApiGeneralException(L"TimeOUT!");
    }
}

NODISCARD unsigned int Process::get_process_id()
{
    DWORD process_id = GetProcessId(m_handle);
    if (!process_id) {
        throw WinApiGeneralException(L"Can't get process-id from the current handle!");
    }

    return process_id;
}

Process Process::create_debugged_process(const std::wstring& process_name, const ArgumentsList& arguments)
{
    STARTUPINFO startup_information{ 0 };
    PROCESS_INFORMATION process_information{ 0 };
    startup_information.cb = sizeof(startup_information);  
    std::wstring commandline = create_commandline(arguments);
    static constexpr LPSECURITY_ATTRIBUTES DEFAULT_SECURITY_ATTRIBUTES = NULL;
    static constexpr BOOL DEFAULT_HANDLE_INHERITANCE = NULL;
    static constexpr BOOL DEFAULT_DW_TYPE = NORMAL_PRIORITY_CLASS | DEBUG_PROCESS | DEBUG_ONLY_THIS_PROCESS;
    static constexpr  LPVOID DEFAULT_INHERIT_ENVIROMENT = NULL;
    static constexpr LPCWSTR DEFAULT_CURNRENT_DIRECTORY = NULL;
    BOOL status = CreateProcessW(process_name.c_str(),
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
        throw WinApiGeneralException(L"Can't Create Process");
    }
    CloseHandle(process_information.hThread); // to prevent a leak...

    return Process(process_information.hProcess);
}

Process::Process(HANDLE handle_to_process) : 
    m_handle(handle_to_process)
{
    
}

Process::Process(Process&& process) : 
    m_handle(std::exchange(process.m_handle, INVALID_HANDLE_VALUE))
{
    
}