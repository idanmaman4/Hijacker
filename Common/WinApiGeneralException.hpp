#pragma once

#include "defines.hpp"

#include <string>
#include <format>

class WinApiGeneralException final
{
public:
	explicit WinApiGeneralException(const std::wstring& message);
	explicit WinApiGeneralException(const std::wstring& message, NTSTATUS nt_status);
	NODISCARD std::wstring what() const; 
	WinApiGeneralException(WinApiGeneralException&) = default;
	WinApiGeneralException(WinApiGeneralException&&) = default;
	~WinApiGeneralException() = default;

	WinApiGeneralException& operator=(WinApiGeneralException&) = delete;
	WinApiGeneralException& operator=(WinApiGeneralException&&) = delete;

private:
	static NODISCARD std::wstring create_message(const std::wstring&  message);
	static NODISCARD std::wstring create_message_with_ntstatus(const std::wstring& message, NTSTATUS nt_status);

	std::wstring m_message;
};