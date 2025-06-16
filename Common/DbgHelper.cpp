#include "DbgHelper.hpp"

void DbgHelper::show_dbg_message(const std::string& message)
{
		if constexpr (DbgHelper::is_mode_debug) {
			try {
				SmartMessageBox  message_box("DBG_HELPER", message);
				message_box.show();
			}
		catch (...){
		}
		}
}

