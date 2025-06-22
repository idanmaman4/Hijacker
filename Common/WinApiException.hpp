#pragma once

#include "Defines.hpp"
#include "DefineWinApi.hpp"

#include <string>
#include <format>

class WinApiException final
{
public:
	explicit WinApiException(const std::wstring& message);
	explicit WinApiException(const std::wstring& message, NTSTATUS nt_status);
	// [CR] Conventions - reorder functions. Dtor after Ctors. Defaults after public APIs
	WinApiException(WinApiException&) = default;
	WinApiException(WinApiException&&) = default;
	~WinApiException() = default;

	NO_DISCARD std::wstring get_message() const; 

	WinApiException& operator=(WinApiException&) = delete;
	WinApiException& operator=(WinApiException&&) = delete;

private:
	static NO_DISCARD std::wstring create_message(const std::wstring& message);
	static NO_DISCARD std::wstring create_message_with_ntstatus(const std::wstring& message, NTSTATUS nt_status);

	std::wstring m_message;
};
