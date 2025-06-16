#include "SmartMessageBox.hpp"

SmartMessageBox::SmartMessageBox(const std::string& title, const std::string& message) : m_message(message), m_title(title)
{
}

void SmartMessageBox::show() const
{
	static constexpr HWND DEFAULT_WINDOW = NULL ;
	static constexpr UINT DEFAULT_MESSAGE_TYHPE = MB_OK;
	int status = MessageBoxA(
		DEFAULT_WINDOW,
		m_message.c_str(),
		m_title.c_str(),
		DEFAULT_MESSAGE_TYHPE
	);
	if (!status) {
		throw WinApiGeneralException("Message Appear Error!");
	}
}
