#pragma once

#include "DefineTypes.hpp"
#include "Defines.hpp"
#include "DefineWinApi.hpp"
#include "GenericException.hpp"
#include "WinApiException.hpp"

#include <string>
#include <vector>
#include <filesystem>


template <typename T>
class BaseParser
{
public:
	explicit BaseParser(const std::wstring& command_line);

	virtual ~BaseParser() = default;

	NO_DISCARD T get_arguments() const;

	BaseParser(BaseParser&) = delete;
	BaseParser(BaseParser&&) = delete;
	BaseParser& operator=(BaseParser&) = delete;
	BaseParser& operator=(BaseParser&&) = delete;

protected:
	NO_DISCARD ArgumentsList get_argument_list() const;
	virtual NO_DISCARD T get_parsed_arguments(ArgumentsList& arguments_raw) const = 0;
	virtual NO_DISCARD bool check_arguments_correctness(ArgumentsList& arguments_raw) const = 0;

private:
	struct ParsedArguments final {
	public:
		explicit ParsedArguments(LPWSTR* arguments, int arguments_count);
		~ParsedArguments();
		ParsedArguments(ParsedArguments&&);

		NO_DISCARD LPWSTR* get_arguments_raw() const;
		NO_DISCARD int get_arguments_count() const;
		
		ParsedArguments(ParsedArguments&) = delete;
		ParsedArguments& operator=(ParsedArguments&) = delete;
		ParsedArguments& operator=(ParsedArguments&&) = delete;

	private: 
		LPWSTR* m_arguments;
		int m_arguments_count;
	};
	 
	static NO_DISCARD ParsedArguments parse_arguments_string(const std::wstring& command_line);

	ParsedArguments m_command_parsed;
};


template<typename T>
inline BaseParser<T>::BaseParser(const std::wstring& command_line) : 
	m_command_parsed(parse_arguments_string(command_line))
{
}

template<typename T>
inline T BaseParser<T>::get_arguments() const
{
	ArgumentsList arguments = get_argument_list();
	if (!check_arguments_correctness(arguments)) {
		throw GenericException(L"can't parse arguments! -> wrong arguments, plz check the supplied arguments...");
	}

	return get_parsed_arguments(arguments);
}

template<typename T>
inline ArgumentsList BaseParser<T>::get_argument_list() const
{
	return ArgumentsList(m_command_parsed.get_arguments_raw(), m_command_parsed.get_arguments_raw() + m_command_parsed.get_arguments_count());
}


template<typename T>
inline BaseParser<T>::ParsedArguments BaseParser<T>::parse_arguments_string(const std::wstring& command_line)
{
	int arguments_count;
	if (command_line.empty()) {
		throw GenericException(L"Unable To parse empty commandline!");
	}
	LPWSTR * command_parsed = CommandLineToArgvW(command_line.c_str(), &arguments_count);
    if (!command_parsed) {
        throw WinApiException(L"Unable To parse command Line!");
    }

    return BaseParser<T>::ParsedArguments{command_parsed, arguments_count};
}

template<typename T>
inline BaseParser<T>::ParsedArguments::ParsedArguments(LPWSTR* arguments, int arguments_count) : m_arguments(arguments), m_arguments_count(arguments_count)
{
}

template<typename T>
inline BaseParser<T>::ParsedArguments::~ParsedArguments()
{
	try {
		if (m_arguments != nullptr) {
			LocalFree(m_arguments);
		}
	}
	catch (...) {
	}

}

template<typename T>
inline BaseParser<T>::ParsedArguments::ParsedArguments(ParsedArguments&& parsed_arguments) : 
	m_arguments(std::exchange(parsed_arguments.m_arguments, nullptr)),
	m_arguments_count(std::exchange(parsed_arguments.m_arguments_count, 0))
{
}

template<typename T>
inline LPWSTR* BaseParser<T>::ParsedArguments::get_arguments_raw() const
{
	return m_arguments;
}

template<typename T>
inline int BaseParser<T>::ParsedArguments::get_arguments_count() const
{
	return m_arguments_count;
}
