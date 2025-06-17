 #pragma once // [CR] Remove Space

#include "WinApiGeneralException.hpp"

#include <string>

// [CR] Remove New Line
// [CR] Design - Why is this needed?
class SmartMessageBox final
{
public:
	// [CR] Why ASCII string?
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

