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
	NODISCARD T get_arguments() const;
	virtual ~BaseParser() = default;

	BaseParser(BaseParser&) = delete;
	BaseParser(BaseParser&&) = delete;
	BaseParser& operator=(BaseParser&) = delete;
	BaseParser& operator=(BaseParser&&) = delete;

protected:
	NODISCARD ArgumentsList get_argument_list() const;
	virtual NODISCARD T get_arguments_parsing(ArgumentsList& arguments_raw) const = 0;
	virtual NODISCARD bool check_arguments_correctness(ArgumentsList& arguments_raw) const;

private:
	struct m_ParsedArguments { //ADT : just holds data without any logic!
		SafeNativeParsedArguments arguments;
		int arguments_count;
	};

	static NODISCARD m_ParsedArguments parse_arguments_string(const std::wstring& command_line);
	m_ParsedArguments m_command_parsed;
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

	return get_arguments_parsing(arguments);
}

template<typename T>
inline ArgumentsList BaseParser<T>::get_argument_list() const
{
	return ArgumentsList(m_command_parsed.arguments.get(), m_command_parsed.arguments.get() + m_command_parsed.arguments_count);
}

template<typename T>
inline bool BaseParser<T>::check_arguments_correctness(UNUSED ArgumentsList& arguments_raw) const
{
	return true;
}

template<typename T>
inline BaseParser<T>::m_ParsedArguments BaseParser<T>::parse_arguments_string(const std::wstring& command_line)
{
	int nubmer_of_arguments;
	if (command_line.empty()) {
		throw GenericException(L"Unable To parse empty commandline!");
	}
	SafeNativeParsedArguments arguments = make_safe_native_parsed_arguments(CommandLineToArgvW(command_line.c_str(), &nubmer_of_arguments));
    if (!arguments) {
        throw WinApiGeneralException(L"Unable To parse command Line!");
    }

    return {std::move(arguments), nubmer_of_arguments};
}
