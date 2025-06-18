#include "UserOutput.hpp"
#include "WinApiGeneralException.hpp"
#include "InjectorBusinessLogic.hpp"
#include "defines.hpp"
#include "DbgHelper.hpp"
#include "Registry.hpp"

#include <iostream>

// This is a really good work.
//
// Strengths:
// * You use all sort of features of the language.
// * You show understanding of lifetime issues and resource management
// * and your code looks pretty good.
// * Some of your designs are pretty smart, even if I wouldn't choose them myself.
//
// Weaknesses:
// * I did took minor things and commented on them - a lot, so you do need to improve with some of the conventions.
// * I do want to talk about something in your Registry class
// * I think that some of your class can be designed in a simpler way
// 

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