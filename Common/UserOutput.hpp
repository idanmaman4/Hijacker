 #pragma once

#include "WinApiGeneralException.hpp"

#include <string>

//CR: [implementation] Why is this a class?
class UserOutput final
{
public:
	//CR: [naming] breathe
	static void show_messagebox(const std::wstring& title, const std::wstring& message);

	~UserOutput() = delete;
	UserOutput() = delete;
	UserOutput(UserOutput&) = delete;
	UserOutput(UserOutput&&) = delete;
	UserOutput& operator= (UserOutput&) = delete;
	UserOutput& operator= (UserOutput&&) = delete;
};

