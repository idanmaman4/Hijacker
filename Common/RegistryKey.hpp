#pragma once

#include "Defines.hpp"
#include "DefineWinApi.hpp"
#include "WinApiException.hpp"
#include "ConstRegistryKey.hpp"
#include "ConstRegistryKey.hpp"

#include<filesystem>

class RegistryKey final
{
public:



	explicit RegistryKey(const ConstRegistryKey& parent_key, const std::filesystem::path& registry_path);
	explicit RegistryKey(const std::filesystem::path& registry_path);
	~RegistryKey();

	void write(const std::wstring& value_name, const std::wstring& value_conent);
	NO_DISCARD RegistryKey create_key(const std::wstring& key_name);

	RegistryKey(RegistryKey&) = delete;
	RegistryKey(RegistryKey&&) = delete;
	RegistryKey& operator=(RegistryKey&) = delete;
	RegistryKey& operator= (RegistryKey&&) = delete;


private:
	explicit RegistryKey(HKEY key);

	static NO_DISCARD HKEY open_registry_key(const ConstRegistryKey& base_key, const std::filesystem::path& registry_path);

	HKEY m_key;
};
