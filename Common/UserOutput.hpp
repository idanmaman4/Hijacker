 #pragma once

#include "WinApiException.hpp"

#include <string>

namespace UserOutput
{
	void show_message_box(const std::wstring& title, const std::wstring& message);
};

