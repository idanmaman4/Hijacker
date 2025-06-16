#include "SmartMessageBox.hpp"
#include "WinApiGeneralException.hpp"
#include "DbgHelper.hpp"

#include <iostream>
#include <Windows.h>

#define UNUSED [[maybe_unused]]

#define SMART_CATCH(TYPE,RETURN_CODE) catch(TYPE& exception){\
    DbgHelper::show_dbg_message(exception.what());\
    return static_cast<int>(RETURN_CODE);\
    }\

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
// [CR] Nice. Now do the same, but start the original program
int WINAPI WinMain(
    UNUSED _In_ HINSTANCE hInstance,
    UNUSED _In_opt_ HINSTANCE hPrevInstance,
    UNUSED _In_ LPSTR lpCmdLine,
    UNUSED _In_ int nShowCmd
) {
    try{
        SmartMessageBox message_box("INJECTEE", "Injected");
        message_box.show();
    }
    SMART_CATCH(WinApiGeneralException, STATUS_CODE::WINAPI_ERROR)
    SMART_CATCH_ELSE()

    return static_cast<int>(STATUS_CODE::SUCCESS);
}