#pragma once

#include "defines.hpp"

#include <string>
#include <format>


class WinApiGeneralException final
{
public:
	explicit WinApiGeneralException(const std::string& message);
	NODISCARD std::string what() const; 

	WinApiGeneralException(WinApiGeneralException&) = default;
	WinApiGeneralException(WinApiGeneralException&&) = default;
	~WinApiGeneralException() = default;
	
	WinApiGeneralException& operator= (WinApiGeneralException&) = delete;
	WinApiGeneralException& operator= (WinApiGeneralException&&) = delete;

private:
	static NODISCARD std::string create_message(const std::string&  message);
	std::string m_message;
};

