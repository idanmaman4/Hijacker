#include "WinApiException.hpp"
#include "InjectorBusinessLogic.hpp"
#include "Defines.hpp"
#include "DebugHelper.hpp"

#include <iostream>

static int WINAPI wWinMain(IN HINSTANCE UNUSED(hInstance),
    IN HINSTANCE UNUSED(hPrevInstance),
    IN LPWSTR lpCmdLine,
    IN int UNUSED(nShowCmd)) {
    try{
        InjectorCommnadLineParser cmd_parser(lpCmdLine);
        CommandLineArgs parsed_args = cmd_parser.get_arguments();
        InjectorBusinessLogic business_logic(parsed_args.program_name, parsed_args.injectee_name);
        business_logic.main_logic();
    }
    CATCH_ALL()

    return static_cast<int>(StatusCode::SUCCESS);
}
