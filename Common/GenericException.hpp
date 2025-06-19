#pragma once

#include "Defines.hpp"

#include <string>
#include <format>

class GenericException final
{
public:
	explicit GenericException(const std::wstring& message);
	
	GenericException(GenericException&) = default;
	GenericException(GenericException&&) = default;
	~GenericException() = default;

	NO_DISCARD std::wstring get_message() const;

	GenericException& operator=(GenericException&) = delete;
	GenericException& operator=(GenericException&&) = delete;

private:
	static NO_DISCARD std::wstring create_message(const std::wstring&  message);

	std::wstring m_message;
};

