#include "GenericException.hpp"

GenericException::GenericException(const std::string& message) : 
	m_message(create_message(message))
{
}

std::string GenericException::what() const
{
	return m_message;
}

std::string GenericException::create_message(const std::string& message)
{
	return  std::format("GeneralException : {}", message);
}
