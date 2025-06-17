#include "InjecteeBussinesLogic.hpp"

InjecteeBussinesLogic::InjecteeBussinesLogic(const std::filesystem::path& program_name, const ArgumentsList& arguments) : 
    m_program_name(program_name), 
    m_arguments(arguments)
{
}

void InjecteeBussinesLogic::main_logic()
{
    static const std::wstring MESSAGE_BOX_TILE = L"INJECTEE";
    static const std::wstring MESSAGE_BOX_MESSAGE = L"Injected...";
    UserOutput::show_messagebox(MESSAGE_BOX_TILE, MESSAGE_BOX_MESSAGE);
    Process process{ Process::create_process_debug(m_program_name.wstring(), m_arguments) };
    process.wait();
}
