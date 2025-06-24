#pragma once

#include "RegistryKey.hpp"

const RegistryKey::ConstRegistryKey RegistryKey::ConstRegistryKey::REGISTRY_CLASSES_ROOT{HKEY_CLASSES_ROOT};
const RegistryKey::ConstRegistryKey RegistryKey::ConstRegistryKey::REGISTRY_CURRENT_CONFIG{HKEY_CURRENT_CONFIG};
const RegistryKey::ConstRegistryKey RegistryKey::ConstRegistryKey::REGISTRY_CURRENT_USER{HKEY_CURRENT_USER};
const RegistryKey::ConstRegistryKey RegistryKey::ConstRegistryKey::REGISTRY_LOCAL_MACHINE {HKEY_LOCAL_MACHINE};
const RegistryKey::ConstRegistryKey RegistryKey::ConstRegistryKey::REGISTRY_USERS{HKEY_USERS};

RegistryKey::RegistryKey(const RegistryKey::ConstRegistryKey& parent_key, const std::filesystem::path& registry_path) : 
	m_key(open_registry_key(parent_key, registry_path))
{
}


RegistryKey::RegistryKey(const std::filesystem::path& registry_path) :
	m_key(open_registry_key(RegistryKey::ConstRegistryKey::REGISTRY_CURRENT_USER, registry_path))
{
}

RegistryKey::~RegistryKey()
{
	try {
		RegCloseKey(m_key);		
	}
	catch (...) {
	}
}

RegistryKey::RegistryKey(HKEY key) : 
	m_key(key) 
{
}

RegistryKey::ConstRegistryKey::ConstRegistryKey(HKEY key) :
	m_key(key)
{
}

void RegistryKey::write(const std::wstring& value_name, const std::wstring& value_conent)
{
	static constexpr DWORD ALLOWD_DW_TYPE = REG_SZ;
	static constexpr DWORD DEFAULT_RESERVED = 0;
	LSTATUS status = RegSetValueExW(m_key,
		value_name.c_str(), 
		DEFAULT_RESERVED,
		ALLOWD_DW_TYPE, 
		static_cast<BYTE*>(static_cast<void*>(const_cast<wchar_t *>(value_conent.c_str()))), 
		(static_cast<DWORD>(value_conent.size()) + 1) * sizeof(wchar_t)
	);
	if (NT_ERROR(status)) {
		throw WinApiException(L"RegistryKey Write Error!", status);
	}
}

RegistryKey RegistryKey::create_key(const std::wstring& key_name)
{
	HKEY result;
	LSTATUS status = RegCreateKeyW(m_key,
		key_name.c_str(),
		&result
	);
	if (NT_ERROR(status)) {
		throw WinApiException(L"RegistryKey Creation Error!", status);
	}

	return RegistryKey{ result };
}

HKEY RegistryKey::open_registry_key(const RegistryKey::ConstRegistryKey& base_key, const std::filesystem::path& registry_path)
{
	HKEY result;
	LSTATUS status = RegOpenKeyW(base_key.get_raw_handle(),
		registry_path.wstring().c_str(),
		&result
	);
	if (NT_ERROR(status)) {
		throw WinApiException(L"RegistryKey Open Error!", status);
	}

	return result;
}

NO_DISCARD HKEY RegistryKey::ConstRegistryKey::get_raw_handle() const
{
	return m_key;
}
