#pragma once

#include "defines.hpp"
#include "WinApiGeneralException.hpp"

#include<filesystem>


class Registry final
{
public:
	explicit Registry(const Registry& parent_key, const std::filesystem::path& registry_path);
	explicit Registry(const std::filesystem::path& registry_path);
	void write(const std::wstring& value_name, const std::wstring& value_conent);
	NODISCARD Registry create_key(const std::wstring& key_name);
	~Registry();

	const static Registry REGISTRY_CLASSES_ROOT;
	const static Registry REGISTRY_CURRENT_CONFIG;
	const static Registry REGISTRY_CURRENT_USER;
	const static Registry REGISTRY_LOCAL_MACHINE;
	const static Registry REGISTRY_USERS;

private:
	explicit Registry(HKEY key);
	static NODISCARD HKEY open_registry_key(const Registry& base_key, const std::filesystem::path& registry_path);

	HKEY m_key;
	bool m_owns_handle;
};

