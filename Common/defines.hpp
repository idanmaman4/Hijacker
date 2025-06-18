//CR: [conventions] Filename doesn't stand with conventions
#pragma once

#define WIN32_NO_STATUS
#include <windows.h>
#include <dbghelp.h>
#undef WIN32_NO_STATUS

//CR: [efficiency] Do everyone who includes this header needs those includes?
#include <winternl.h>
#include <ntstatus.h>
#include <string>
#include <vector>

//CR: [conventions] CamelCase for enum
enum class STATUS_CODE {
    SUCCESS = 0,
    GENERIC_ERROR,
    WINAPI_ERROR,
    UNKOWN

};

//CR: [misc] let it breathe, NO_DISCARD
#define NODISCARD [[nodiscard]]

//CR: [misc] We like using the maybe unused in a way that wraps the param
//           Also, sometimes its better to put the [[maybe_unused]] after the param.
#define UNUSED [[maybe_unused]]

//CR: [misc] We do not like macros and prefer to use them in a spceific amount of use-cases.
//           This one is too ugly, taking the type as a param as if it's a
//           macro implementation of templates is ugly.
//CR: [conventions] Have a space before { and before \. let them breathe.
#define SMART_CATCH(TYPE,RETURN_CODE) catch(TYPE& exception){\
    DbgHelper::show_dbg_message(exception.what());\
    return static_cast<int>(RETURN_CODE);\
//CR: [conventions] Bad indent
    }

#define SMART_CATCH_ELSE() catch (...) {\
        DbgHelper::show_dbg_message(L"UNKWON EXCEPTION!");\
        return static_cast<int>(STATUS_CODE::UNKOWN);\
    }

#define SMART_CATCH_ALL() SMART_CATCH(WinApiGeneralException, STATUS_CODE::WINAPI_ERROR)\
        SMART_CATCH(GenericException, STATUS_CODE::GENERIC_ERROR)\
        SMART_CATCH_ELSE()

using ArgumentsList = std::vector<std::wstring>;
//CR: [convetions] Put newline in end of file.