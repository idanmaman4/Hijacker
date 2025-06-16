#pragma once

#include "InjectorCommnadLineParser.hpp"
#include "InjectorCommnadLineParser.hpp"
#include "Registry.hpp"

#include<filesystem>


class InjectorBusinessLogic
{
public:
	explicit InjectorBusinessLogic(std::filesystem::path program_name,std::filesystem::path injectee );
	
	void main_logic() const;

	~InjectorBusinessLogic() = default;

	InjectorBusinessLogic(InjectorBusinessLogic&) = delete;
	InjectorBusinessLogic(InjectorBusinessLogic&&) = delete;
	InjectorBusinessLogic& operator= (InjectorBusinessLogic&) = delete;
	InjectorBusinessLogic& operator= (InjectorBusinessLogic&&) = delete;

private: 
	std::filesystem::path m_program_name;
	std::filesystem::path m_injectee;
};

