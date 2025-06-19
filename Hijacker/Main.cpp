#include "WinApiException.hpp"
#include "InjecteeCommandLineParser.hpp"
#include "InjecteeBussinesLogic.hpp"
#include "DebugHelper.hpp"

#include <iostream>
#include <Windows.h>
#include <Process.h>

int WINAPI wWinMain(IN HINSTANCE UNUSED(hInstance),
    IN HINSTANCE UNUSED(hPrevInstance),
    IN LPWSTR lpCmdLine, 
    IN int UNUSED(nShowCmd)) {
    try{
        InjecteeCommandLineParser cmd_parser(lpCmdLine);
        InjecteeCommandLineArgs parsed_args = cmd_parser.get_arguments();
        InjecteeBussinesLogic bussines_logic(parsed_args.program_name, parsed_args.arguments);
        bussines_logic.main_logic();
    }
    CATCH_ALL()

    return static_cast<int>(StatusCode::SUCCESS);
}