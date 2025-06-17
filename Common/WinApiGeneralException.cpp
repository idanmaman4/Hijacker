#include "WinApiGeneralException.hpp"

WinApiGeneralException::WinApiGeneralException(const std::wstring& message) : 
	m_message(create_message(message))
{
}

WinApiGeneralException::WinApiGeneralException(const std::wstring& message, NTSTATUS nt_status):
	m_message(create_message_with_ntstatus(message, nt_status))
{
}

std::wstring WinApiGeneralException::what() const
{
	return m_message;
}

std::wstring WinApiGeneralException::create_message(const std::wstring& message)
{
	return std::format(L"WinAPI GeneralException : {} Error Numnber:{}", message , GetLastError() );
}

std::wstring WinApiGeneralException::create_message_with_ntstatus(const std::wstring& message, NTSTATUS nt_status)
{
	return std::format(L"WinAPI GeneralException : NTSTATUS: {} : {} Error Numnber:{}", nt_status, message, GetLastError());
}
