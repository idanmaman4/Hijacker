#pragma once

#include "defines.hpp"

#include <string>
#include <format>

class GenericException final
{
public:
	explicit GenericException(const std::wstring& message);
	//CR: [conventions] public functions after ctor and dtor
	//CR: [misc] trailing whitespace
	//CR: [naming] This is not a good name for an exception message
	NODISCARD std::wstring what() const;
	//CR: [conventions] default implemented-ctors after ctor, dtor, public functions
	GenericException(GenericException&) = default;
	GenericException(GenericException&&) = default;
	~GenericException() = default;
	
	GenericException& operator=(GenericException&) = delete;
	GenericException& operator=(GenericException&&) = delete;

private:
	static NODISCARD std::wstring create_message(const std::wstring&  message);

	std::wstring m_message;
};

