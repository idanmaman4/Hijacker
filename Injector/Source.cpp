#include "SmartMessageBox.hpp"
#include "WinApiGeneralException.hpp"
#include "InjectorBusinessLogic.hpp"
#include "defines.hpp"
#include "DbgHelper.hpp"
#include "Registry.hpp"
#include "InjectorCommnadLineParser.hpp"

#include <iostream>
#include <Windows.h>

// [CR] General - File name - Source is not indicative, use Main
// [CR] Implementation - code duplication
#define SMART_CATCH(TYPE,RETURN_CODE) catch(TYPE& exception){\
    DbgHelper::show_dbg_message(exception.what());\
    return static_cast<int>(RETURN_CODE);\
    }

#define SMART_CATCH_ELSE() catch (...) {\
        DbgHelper::show_dbg_message("UNKWON EXCEPTION!");\
        return static_cast<int>(STATUS_CODE::UNKOWN);\
    }

enum class STATUS_CODE {
    SUCCESS = 0 ,
    FAILED_ARGS , 
    WINAPI_ERROR,
    UNKOWN

};

int WINAPI wWinMain(
    UNUSED _In_ HINSTANCE hInstance,
    UNUSED _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    UNUSED _In_ int nShowCmd
) {
    try{
        InjectorCommnadLineParser cmd_parser(lpCmdLine);
        InjectorCommnadLineParser::command_line_args parsed_args = cmd_parser.get_args();
        InjectorBusinessLogic business_logic(parsed_args.program_name, parsed_args.injectee_name);
        business_logic.main_logic();
    }
    SMART_CATCH(WinApiGeneralException, STATUS_CODE::WINAPI_ERROR)
    SMART_CATCH_ELSE()

    return static_cast<int>(STATUS_CODE::SUCCESS);
}