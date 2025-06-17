#include "UserOutput.hpp"

void UserOutput::show_messagebox(const std::wstring& title, const std::wstring& message)
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
		throw WinApiGeneralException(L"Message Appear Error!");
	}
}
