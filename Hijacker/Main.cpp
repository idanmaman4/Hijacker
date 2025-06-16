#include "WinApiGeneralException.hpp"
#include "InjecteeCommandLineParser.hpp"
#include "InjecteeBussinesLogic.hpp"
#include "DbgHelper.hpp"

#include <iostream>
#include <Windows.h>
#include <Process.h>


enum class STATUS_CODE {
    SUCCESS = 0 ,
    GENERIC_ERROR , 
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
        InjecteeCommandLineParser cmd_parser(lpCmdLine);
        InjecteeCommandLineArgs parsed_args = cmd_parser.get_args();
        InjecteeBussinesLogic bussines_logic(parsed_args.program_name, parsed_args.arguments);
        bussines_logic.main_logic();
    }
    SMART_CATCH(WinApiGeneralException, STATUS_CODE::WINAPI_ERROR)
    SMART_CATCH(GenericException, STATUS_CODE::GENERIC_ERROR)
    SMART_CATCH_ELSE()

    return static_cast<int>(STATUS_CODE::SUCCESS);
}