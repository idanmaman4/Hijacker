#include "Process.hpp"

std::wstring escape_string(const std::wstring& string_to_escape) {
    static const std::wregex pattern(L"\"");
    static const std::wstring replacement(L"\\\"");

    return std::format(L"\"{}\"",std::regex_replace(string_to_escape, pattern, replacement));
}

Process::~Process()
{
    try {
        CloseHandle(m_handle);
    }
    catch (...) {}
}

void Process::stop_debugging(DWORD process_id)
{
    if (!DebugActiveProcessStop(process_id)) {
        throw WinApiGeneralException("Can't detach from process!");
    }
}

void Process::wait(size_t time)
{
    DWORD res = WaitForSingleObject(m_handle,static_cast<DWORD>(time));
    if (res == WAIT_FAILED) {
            throw WinApiGeneralException("Wait has been failed!");
    }
    if (res == WAIT_ABANDONED) {
            throw WinApiGeneralException("TimeOUT!");
    }
}

Process Process::create_process_debug(const std::wstring& process_name, const ArgumentsList& arguments)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    std::wstringstream command_line_string;
    for (const auto& join_arg : arguments | std::views::transform(escape_string) | std::views::join_with(' ')) {
        command_line_string << join_arg;
    }
    static constexpr LPSECURITY_ATTRIBUTES DEFAULT_SECURITY_ATTRIBUTES = NULL;
    static constexpr BOOL DEFAULT_HANDLE_INHERITANCE = NULL;
    static constexpr BOOL DEFAULT_DW_TYPE = NORMAL_PRIORITY_CLASS | DEBUG_PROCESS | DEBUG_ONLY_THIS_PROCESS;
    static constexpr  LPVOID DEFAULT_INHERIT_ENVIROMENT = NULL;
    static constexpr LPCWSTR DEFAULT_CURNRENT_DIRECTORY = NULL;
    BOOL status = CreateProcessW(process_name.c_str(),
        const_cast<LPWSTR>(command_line_string.str().c_str()),
        DEFAULT_SECURITY_ATTRIBUTES,
        DEFAULT_SECURITY_ATTRIBUTES,
        DEFAULT_HANDLE_INHERITANCE,
        DEFAULT_DW_TYPE,
        DEFAULT_INHERIT_ENVIROMENT,
        DEFAULT_CURNRENT_DIRECTORY,
        &si,
        &pi
    );
    if (!status) {
        throw WinApiGeneralException("Can't Create Process");
    }
    CloseHandle(pi.hThread);
    stop_debugging(pi.dwProcessId);

    return Process(pi.hProcess);
}

Process::Process(HANDLE handle_to_process) : m_handle(handle_to_process)
{
}
