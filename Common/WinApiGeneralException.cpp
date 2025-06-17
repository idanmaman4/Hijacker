#include "WinApiGeneralException.hpp"

WinApiGeneralException::WinApiGeneralException(const std::string& message) : 
	m_message(create_message(message))
{
}

std::string WinApiGeneralException::what() const
{
	return m_message;
}

std::string WinApiGeneralException::create_message(const std::string& message)
{
	return  std::format("WinAPI GeneralException : {} Error Numnber:{}", message , GetLastError() );
}
