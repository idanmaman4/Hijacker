#include "DbgHelper.hpp"

void DbgHelper::show_dbg_message(const std::wstring& message)
{
		if constexpr (DbgHelper::is_mode_debug) {
			try {
				static const std::wstring MESSGAEBOX_TITLE = L"DBG_HELPER";
				UserOutput::show_messagebox(MESSGAEBOX_TITLE, message);
			}
			catch (...){
			}
		}
}

