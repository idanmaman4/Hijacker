#include "InjecteeBussinesLogic.hpp"

InjecteeBussinesLogic::InjecteeBussinesLogic(const std::filesystem::path& program_name, const ArgumentsList& arguments) : 
    m_program_name(program_name), 
    Arguments(arguments)
{
}

void InjecteeBussinesLogic::main_logic()
{
    // [CR] Misc - It is weird to use named variables when passing arguments to your own function
    static const std::wstring MESSAGE_BOX_TILE = L"INJECTEE";
    static const std::wstring MESSAGE_BOX_MESSAGE = L"Injected...";
    UserOutput::show_message_box(MESSAGE_BOX_TILE, MESSAGE_BOX_MESSAGE);
    CreatedProcess process(m_program_name.wstring(), Arguments);
    process.stop_debugging();
    process.wait();
}
