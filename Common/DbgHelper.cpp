#include "DbgHelper.hpp"

//CR: [conventions] bad indent
void DbgHelper::show_dbg_message(const std::wstring& message)
{
		if constexpr (DbgHelper::is_mode_debug) {
			try {
				//CR: [misc] typo, prefer MESSAGE_BOX_TITLE, rename Message "Debug Helper"
				static const std::wstring MESSGAEBOX_TITLE = L"DBG_HELPER";
				UserOutput::show_messagebox(MESSGAEBOX_TITLE, message);
			}
			//CR: [misc] space before {}
			catch (...){
			}
		}
}