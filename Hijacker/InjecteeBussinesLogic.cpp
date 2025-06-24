#include "InjecteeBussinesLogic.hpp"

InjecteeBussinesLogic::InjecteeBussinesLogic(const std::filesystem::path& program_name, const ArgumentsList& arguments) : 
    m_program_name(program_name), 
    Arguments(arguments)
{
}

void InjecteeBussinesLogic::main_logic()
{
    UserOutput::show_message_box(L"INJECTEE", L"Injected...");
    DebuggedProcess process(m_program_name.wstring(), Arguments);
    process.stop_debugging();
    process.wait();
}
