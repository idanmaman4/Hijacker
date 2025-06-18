#pragma once

#define WIN32_NO_STATUS
#include <windows.h>
#include <dbghelp.h>
#undef WIN32_NO_STATUS

#include <winternl.h>
#include <ntstatus.h>
#include <string>
#include <vector>

enum class STATUS_CODE {
    SUCCESS = 0,
    GENERIC_ERROR,
    WINAPI_ERROR,
    UNKOWN

};

#define NODISCARD [[nodiscard]]

#define UNUSED [[maybe_unused]]

#define SMART_CATCH(TYPE,RETURN_CODE) catch(TYPE& exception){\
    DbgHelper::show_dbg_message(exception.what());\
    return static_cast<int>(RETURN_CODE);\
    }

#define SMART_CATCH_ELSE() catch (...) {\
        DbgHelper::show_dbg_message(L"UNKWON EXCEPTION!");\
        return static_cast<int>(STATUS_CODE::UNKOWN);\
    }

#define SMART_CATCH_ALL() SMART_CATCH(WinApiGeneralException, STATUS_CODE::WINAPI_ERROR)\
        SMART_CATCH(GenericException, STATUS_CODE::GENERIC_ERROR)\
        SMART_CATCH_ELSE()

using ArgumentsList = std::vector<std::wstring>;