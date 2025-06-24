#pragma once

#include "Defines.hpp"
#include "DefineWinApi.hpp"
#include "WinApiException.hpp"

#include<filesystem>

class RegistryKey final
{
public:
	class ConstRegistryKey final
	{
	public:
		~ConstRegistryKey() = default;

		ConstRegistryKey(ConstRegistryKey&) = delete;
		ConstRegistryKey(ConstRegistryKey&&) = delete;
		ConstRegistryKey& operator=(ConstRegistryKey&) = delete;
		ConstRegistryKey& operator=(ConstRegistryKey&&) = delete;

		static const ConstRegistryKey REGISTRY_CLASSES_ROOT;
		static const ConstRegistryKey REGISTRY_CURRENT_CONFIG;
		static const ConstRegistryKey REGISTRY_CURRENT_USER;
		static const ConstRegistryKey REGISTRY_LOCAL_MACHINE;
		static const ConstRegistryKey REGISTRY_USERS;
		
	private:
		explicit ConstRegistryKey(HKEY key);

		NO_DISCARD HKEY get_raw_handle() const ;
	
		HKEY m_key;

		friend class RegistryKey; 
	};

	explicit RegistryKey(const ConstRegistryKey& parent_key, const std::filesystem::path& registry_path);
	explicit RegistryKey(const std::filesystem::path& registry_path);
	~RegistryKey();

	void write(const std::wstring& value_name, const std::wstring& value_conent);
	NO_DISCARD RegistryKey create_key(const std::wstring& key_name);

	RegistryKey(RegistryKey&) = delete;
	RegistryKey(RegistryKey&&) = delete;
	RegistryKey& operator=(RegistryKey&) = delete;
	RegistryKey& operator=(RegistryKey&&) = delete;

private:
	explicit RegistryKey(HKEY key);

	static NO_DISCARD HKEY open_registry_key(const ConstRegistryKey& base_key, const std::filesystem::path& registry_path);

	HKEY m_key;
};
