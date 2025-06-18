#include "WinApiGeneralException.hpp"
#include "InjecteeCommandLineParser.hpp"
#include "InjecteeBussinesLogic.hpp"
#include "DbgHelper.hpp"

#include <iostream>
#include <Windows.h>
#include <Process.h>

int WINAPI wWinMain(
    //CR: [misc] We prefer wrapping the param like this: UNUSED(HInstance hInsance)
    //CR: [misc] Consider having a macro for the in param.
    //CR: [conventions] this is not how we indent
    UNUSED _In_ HINSTANCE hInstance,
    UNUSED _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    UNUSED _In_ int nShowCmd
) {
    try{
        InjecteeCommandLineParser cmd_parser(lpCmdLine);
        InjecteeCommandLineArgs parsed_args = cmd_parser.get_arguments();
        InjecteeBussinesLogic bussines_logic(parsed_args.program_name, parsed_args.arguments);
        bussines_logic.main_logic();
    }
    SMART_CATCH_ALL()

    return static_cast<int>(STATUS_CODE::SUCCESS);
}