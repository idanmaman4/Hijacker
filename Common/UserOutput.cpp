#include "UserOutput.hpp"

void UserOutput::show_message_box(const std::wstring& title, const std::wstring& message)
{
	static constexpr HWND DEFAULT_WINDOW = NULL ;
	static constexpr UINT DEFAULT_MESSAGE_TYHPE = MB_OK;
	int status = MessageBoxW(
		DEFAULT_WINDOW,
		message.c_str(),
		title.c_str(),
		DEFAULT_MESSAGE_TYHPE
	);
	if (!status) {
		throw WinApiException(L"Message Appear Error!");
	}
}
