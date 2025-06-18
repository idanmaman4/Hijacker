#pragma once

#include "defines.hpp"
#include "GenericException.hpp"
#include "WinApiGeneralException.hpp"

#include <string>
#include <vector>
#include <filesystem>

//CR: [implementation] Suggest me another way to implement this
using SafeNativeParsedArguments = std::unique_ptr<LPWSTR[], decltype(&::LocalFree)>;
//CR: [implementation] Tell me about this static object, when is it created.
static constexpr auto make_safe_native_parsed_arguments = [](LPWSTR* argument) {return SafeNativeParsedArguments{argument, LocalFree };};

template <typename T>
class BaseParser
{
public:
	explicit BaseParser(const std::wstring& command_line);
	//CR: [conventions] public functions after ctor and dtor
	NODISCARD T get_arguments() const;
	virtual ~BaseParser() = default;

	BaseParser(BaseParser&) = delete;
	BaseParser(BaseParser&&) = delete;
	BaseParser& operator=(BaseParser&) = delete;
	BaseParser& operator=(BaseParser&&) = delete;

protected:
	NODISCARD ArgumentsList get_argument_list() const;
	//CR: [naming] I dont understand what this functuon do.
	virtual NODISCARD T get_arguments_parsing(ArgumentsList& arguments_raw) const = 0;
	//CR: [naming] I offer you a verb: validate
	virtual NODISCARD bool check_arguments_correctness(ArgumentsList& arguments_raw) const;

private:
	//CR: [convetions] No m_ prefix here
	//CR: [misc] No comments
	//CR: [implementation] Your new type (SafeNativeParsedArguments) should have had a way to hold the count...
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

//CR: [implementation] Interfaces should be easy to use, hard to misuse. It should be pure in the base class.
template<typename T>
inline bool BaseParser<T>::check_arguments_correctness(UNUSED ArgumentsList& arguments_raw) const
{
	return true;
}

template<typename T>
inline BaseParser<T>::m_ParsedArguments BaseParser<T>::parse_arguments_string(const std::wstring& command_line)
{
	//CR: [naming] Prefer the word "count" over "number_of"
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
