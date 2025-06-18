 #pragma once

#include "WinApiGeneralException.hpp"

#include <string>

class UserOutput final
{
public:
	static void show_messagebox(const std::wstring& title, const std::wstring& message);

	~UserOutput() = delete;
	UserOutput() = delete;
	UserOutput(UserOutput&) = delete;
	UserOutput(UserOutput&&) = delete;
	UserOutput& operator= (UserOutput&) = delete;
	UserOutput& operator= (UserOutput&&) = delete;
};

