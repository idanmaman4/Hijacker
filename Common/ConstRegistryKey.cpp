#include "ConstRegistryKey.hpp"

HKEY ConstRegistryKey::get_raw_key_handle() const
{
	return m_key;
}

ConstRegistryKey::ConstRegistryKey(HKEY key) : m_key(key)
{
}

const ConstRegistryKey ConstRegistryKey::REGISTRY_CLASSES_ROOT{HKEY_CLASSES_ROOT};
const ConstRegistryKey ConstRegistryKey::REGISTRY_CURRENT_CONFIG{HKEY_CURRENT_CONFIG};
const ConstRegistryKey ConstRegistryKey::REGISTRY_CURRENT_USER{HKEY_CURRENT_USER};
const ConstRegistryKey ConstRegistryKey::REGISTRY_LOCAL_MACHINE {HKEY_LOCAL_MACHINE};
const ConstRegistryKey ConstRegistryKey::REGISTRY_USERS{HKEY_USERS};