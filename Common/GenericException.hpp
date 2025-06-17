#pragma once

#include "defines.hpp"

#include <string>
#include <format>


class GenericException final
{
public:
	explicit GenericException(const std::wstring& message);
	NODISCARD std::wstring what() const; 
	GenericException(GenericException&) = default;
	GenericException(GenericException&&) = default;
	~GenericException() = default;
	
	GenericException& operator= (GenericException&) = delete;
	GenericException& operator= (GenericException&&) = delete;

private:
	static NODISCARD std::wstring create_message(const std::wstring&  message);

	std::wstring m_message;
};

