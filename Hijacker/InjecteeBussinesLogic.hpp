#pragma once

#include "DefineTypes.hpp"
#include "UserOutput.hpp"
#include "CreatedProcess.hpp"

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
	ArgumentsList Arguments;
};

