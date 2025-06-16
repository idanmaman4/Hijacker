#include "InjectorBusinessLogic.hpp"

// [CR] Conventions - each intialized member on a new line
InjectorBusinessLogic::InjectorBusinessLogic(std::filesystem::path program_name, std::filesystem::path injectee) : m_program_name(program_name), m_injectee(injectee)
{
}

void InjectorBusinessLogic::main_logic() const
{
    // [CR] Greate, elegant code
    static constexpr std::string_view IFEO_REGISTGRY_PATH = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options";
    Registry parent_key(Registry::REGISTRY_LOCAL_MACHINE, IFEO_REGISTGRY_PATH);
    Registry key = parent_key.create_key(m_program_name.string());
    static const std::string IFEO_DEBUGGER_VALUE_NAME = "debugger";
    key.write(IFEO_DEBUGGER_VALUE_NAME, m_injectee.string()); 
}
