#pragma once

#include "defines.hpp"

#include <string>
#include <format>
#include <Windows.h>


class GenericException final
{
public:
	explicit GenericException(const std::string& message);
	NODISCARD std::string what() const; 

	GenericException(GenericException&) = default;
	GenericException(GenericException&&) = default;
	~GenericException() = default;
	
	GenericException& operator= (GenericException&) = delete;
	GenericException& operator= (GenericException&&) = delete;

private:
	static NODISCARD std::string create_message(const std::string&  message);
	std::string m_message;
};

