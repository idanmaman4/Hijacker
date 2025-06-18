#pragma once

#include "Registry.hpp"

const Registry Registry::REGISTRY_CLASSES_ROOT{HKEY_CLASSES_ROOT};
const Registry Registry::REGISTRY_CURRENT_CONFIG{HKEY_CURRENT_CONFIG};
const Registry Registry::REGISTRY_CURRENT_USER{HKEY_CURRENT_USER};
const Registry Registry::REGISTRY_LOCAL_MACHINE {HKEY_LOCAL_MACHINE};
const Registry Registry::REGISTRY_USERS{HKEY_USERS};

Registry::Registry(const Registry& parent_key, const std::filesystem::path& registry_path) : 
	//CR: [misc] spaces
	m_key(open_registry_key(parent_key,registry_path)), 
	m_owns_handle(true)
{
}

Registry::Registry(const std::filesystem::path& registry_path) : 
	m_key(open_registry_key(REGISTRY_CURRENT_USER,registry_path)),
	m_owns_handle(true)
{
}

Registry::~Registry()
{
	try {
		//CR: [design] In a world where all classes are properly designed, you don't need such a thing.
		//             Your RegistryKey class should hold only RAII instances of keys and not floating handles.
		if (m_owns_handle) {
			RegCloseKey(m_key);
		}		
	}
	catch (...) {}
}

void Registry::write(const std::wstring& value_name, const std::wstring& value_conent)
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
		throw WinApiGeneralException(L"Registry Write Error!", status);
	}
}

Registry Registry::create_key(const std::wstring& key_name)
{
	HKEY result;
	//CR: [conventions] This is not how we indent.
	LSTATUS status = RegCreateKeyW( 
		m_key,
		key_name.c_str(),
		&result
	);
	if (NT_ERROR(status)) {
		throw WinApiGeneralException(L"Registry Creation Error!", status);
	}

	return Registry{ result };
}

HKEY Registry::open_registry_key(const Registry& base_key, const std::filesystem::path& registry_path)
{
	HKEY result;
	LSTATUS status = RegOpenKeyW( 
		base_key.m_key,
		registry_path.wstring().c_str(),
		&result
	);
	if (NT_ERROR(status)) {
		throw WinApiGeneralException(L"Registry Open Error!", status);
	}

	return result;
}

Registry::Registry(HKEY key) : 
	m_key(key), 
	m_owns_handle(false)
{
}
