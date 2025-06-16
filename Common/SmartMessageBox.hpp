#pragma once

#include "WinApiGeneralException.hpp"

#include <string>
#include <Windows.h>


class SmartMessageBox final
{
public:
	explicit SmartMessageBox(const std::string& title, const std::string& message);
	void show() const; 

	~SmartMessageBox() = default;

	SmartMessageBox(SmartMessageBox&) = delete;
	SmartMessageBox(SmartMessageBox&&) = delete;
	SmartMessageBox& operator= (SmartMessageBox&) = delete;
	SmartMessageBox& operator= (SmartMessageBox&&) = delete;

private:
	std::string m_message;
	std::string m_title;
};

