#include "UserOutput.hpp"
#include "WinApiGeneralException.hpp"
#include "InjectorBusinessLogic.hpp"
#include "defines.hpp"
#include "DbgHelper.hpp"
#include "Registry.hpp"

#include <iostream>

int WINAPI wWinMain(
    UNUSED _In_ HINSTANCE hInstance,
    UNUSED _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    UNUSED _In_ int nShowCmd
) {
    try{
        InjectorCommnadLineParser cmd_parser(lpCmdLine);
        CommandLineArgs parsed_args = cmd_parser.get_arguments();
        InjectorBusinessLogic business_logic(parsed_args.program_name, parsed_args.injectee_name);
        business_logic.main_logic();
    }
    SMART_CATCH_ALL()

    return static_cast<int>(STATUS_CODE::SUCCESS);
}