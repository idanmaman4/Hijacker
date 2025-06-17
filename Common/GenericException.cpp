#include "GenericException.hpp"

GenericException::GenericException(const std::wstring& message) : 
	m_message(create_message(message))
{
}

std::wstring GenericException::what() const
{
	return m_message;
}

std::wstring GenericException::create_message(const std::wstring& message)
{
	return  std::format(L"GeneralException : {}", message);
}
