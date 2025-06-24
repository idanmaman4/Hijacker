#pragma once

#include "InjectorCommnadLineParser.hpp"
#include "RegistryKey.hpp"

#include <filesystem>

class InjectorBusinessLogic final
{
public:
	explicit InjectorBusinessLogic(const std::filesystem::path& program_name, const std::filesystem::path& injectee);
	
	void main_logic();
	
	~InjectorBusinessLogic() = default;

	InjectorBusinessLogic(InjectorBusinessLogic&) = delete;
	InjectorBusinessLogic(InjectorBusinessLogic&&) = delete;
	InjectorBusinessLogic& operator=(InjectorBusinessLogic&) = delete;
	InjectorBusinessLogic& operator=(InjectorBusinessLogic&&) = delete;

private: 
	std::filesystem::path m_program_name;
	std::filesystem::path m_injectee;
};
