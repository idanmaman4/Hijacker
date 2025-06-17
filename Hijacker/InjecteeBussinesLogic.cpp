#include "InjecteeBussinesLogic.hpp"

InjecteeBussinesLogic::InjecteeBussinesLogic(const std::filesystem::path& program_name, const ArgumentsList& arguments) : 
    m_program_name(program_name), 
    m_arguments(arguments)
{
}

void InjecteeBussinesLogic::main_logic()
{
    SmartMessageBox message_box("INJECTEE", "Injected...");
    message_box.show();
    Process process{ Process::create_process_debug(m_program_name.wstring(), m_arguments) };
    process.wait();
}
