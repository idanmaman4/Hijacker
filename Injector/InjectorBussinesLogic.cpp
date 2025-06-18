#include "InjectorBusinessLogic.hpp"

//CR: [misc] space
InjectorBusinessLogic::InjectorBusinessLogic(const std::filesystem::path& program_name,const std::filesystem::path& injectee) : 
    m_program_name(program_name), 
    m_injectee(injectee)
{
}

void InjectorBusinessLogic::main_logic()
{
    static constexpr std::string_view IFEO_REGISTGRY_PATH = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Image File Execution Options";
    Registry parent_key(Registry::REGISTRY_LOCAL_MACHINE, IFEO_REGISTGRY_PATH);
    Registry key = parent_key.create_key(m_program_name.wstring());
    static const std::wstring IFEO_DEBUGGER_VALUE_NAME = L"debugger";
    key.write(IFEO_DEBUGGER_VALUE_NAME, m_injectee.wstring()); 
}
