#pragma once

#include "defines.hpp"
#include "GenericException.hpp"
#include "WinApiGeneralException.hpp"

#include <string>
#include <vector>
#include <filesystem>


using SafeNativeParsedArguments = std::unique_ptr<LPWSTR[], decltype(&::LocalFree)>;
static constexpr auto make_safe_native_parsed_arguments = [](LPWSTR* argument) {return SafeNativeParsedArguments{argument, LocalFree };};

template <typename T>
class BaseParser
{
public:
	
	explicit BaseParser(const std::wstring& command_line);

	virtual NODISCARD T get_args() const = 0;

	virtual ~BaseParser() = default;

	BaseParser(BaseParser&) = delete;
	BaseParser(BaseParser&&) = delete;
	BaseParser& operator= (BaseParser&) = delete;
	BaseParser& operator= (BaseParser&&) = delete;

protected:
	NODISCARD ArgumentsList get_argument_list() const;

private:
	
	struct ParsedArguments { //ADT : just holds data without any logic!
		SafeNativeParsedArguments arguments;
		int arguments_count;
	};

	static NODISCARD ParsedArguments parse_arguments_string(const std::wstring& command_line);
	ParsedArguments m_command_parsed;
};


template<typename T>
inline BaseParser<T>::BaseParser(const std::wstring& command_line) : 
	m_command_parsed(parse_arguments_string(command_line))
{
}

template<typename T>
inline NODISCARD ArgumentsList BaseParser<T>::get_argument_list() const
{
	return ArgumentsList(m_command_parsed.arguments.get(), m_command_parsed.arguments.get() + m_command_parsed.arguments_count);
}

template<typename T>
inline NODISCARD BaseParser<T>::ParsedArguments BaseParser<T>::parse_arguments_string(const std::wstring& command_line)
{
	int nubmer_of_arguments;
	if (command_line .empty()) {
	        throw GenericException("Unable To parse empty commandline!");
	}
	SafeNativeParsedArguments arguments = make_safe_native_parsed_arguments(CommandLineToArgvW(command_line.c_str(), &nubmer_of_arguments));
    if (!arguments) {
        throw WinApiGeneralException("Unable To parse command Line!");
    }

    return {std::move(arguments), nubmer_of_arguments};
}
