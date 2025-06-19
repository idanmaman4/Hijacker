#include "WinApiException.hpp"

WinApiException::WinApiException(const std::wstring& message) : 
	m_message(create_message(message))
{
}

WinApiException::WinApiException(const std::wstring& message, NTSTATUS nt_status):
	m_message(create_message_with_ntstatus(message, nt_status))
{
}

std::wstring WinApiException::get_message() const
{
	return m_message;
}

std::wstring WinApiException::create_message(const std::wstring& message)
{
	return std::format(L"WinAPI GeneralException : {} Error Numnber:{}", message , GetLastError() );
}

std::wstring WinApiException::create_message_with_ntstatus(const std::wstring& message, NTSTATUS nt_status)
{
	return std::format(L"WinAPI GeneralException : NTSTATUS: {} : {} Error Numnber:{}", nt_status, message, GetLastError());
}
