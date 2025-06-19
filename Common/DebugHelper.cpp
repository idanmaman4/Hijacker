#include "DebugHelper.hpp"

void DebugHelper::show_debug_message(const std::wstring& message)
{
	if constexpr (DebugHelper::is_debug_mode) {
		try {
			static const std::wstring MESSAGE_BOX_TITLE = L"DBG_HELPER";
			UserOutput::show_message_box(MESSAGE_BOX_TITLE, message);
		}
		catch (...) {
		}
	}
}
