#pragma once

#include "defines.hpp"
#include "UserOutput.hpp"
#include "Process.hpp"

#include <filesystem>

class InjecteeBussinesLogic final
{
public:
	explicit InjecteeBussinesLogic(const std::filesystem::path& program_name,const ArgumentsList& arguments);
	void main_logic();
	~InjecteeBussinesLogic() = default;

	InjecteeBussinesLogic(InjecteeBussinesLogic&) = delete;
	InjecteeBussinesLogic(InjecteeBussinesLogic&&) = delete;
	InjecteeBussinesLogic& operator= (InjecteeBussinesLogic&) = delete;
	InjecteeBussinesLogic& operator= (InjecteeBussinesLogic&&) = delete;

private: 
	std::filesystem::path m_program_name;
	ArgumentsList m_arguments;
};

