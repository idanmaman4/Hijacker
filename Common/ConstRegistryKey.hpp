#pragma once

#include "Defines.hpp"
#include "DefineWinApi.hpp"
// [CR] Design - Why not enum class? 
class ConstRegistryKey final
{
public:
	// [CR] Conventions - Static members after non-static API
	// [CR] Convetions - static const?
	const static ConstRegistryKey REGISTRY_CLASSES_ROOT;
	const static ConstRegistryKey REGISTRY_CURRENT_CONFIG;
	const static ConstRegistryKey REGISTRY_CURRENT_USER;
	const static ConstRegistryKey REGISTRY_LOCAL_MACHINE;
	const static ConstRegistryKey REGISTRY_USERS;

	~ConstRegistryKey() = default;
	// [CR] Design - Public API that returns HKEY is an aethetic problem.
	NO_DISCARD HKEY get_raw_key_handle() const;

	ConstRegistryKey(ConstRegistryKey&) = delete;
	ConstRegistryKey(ConstRegistryKey&&) = delete;
	ConstRegistryKey& operator=(ConstRegistryKey&) = delete;
	ConstRegistryKey& operator=(ConstRegistryKey&&) = delete;

private:
	explicit ConstRegistryKey(HKEY key);
	
	HKEY m_key;
};
