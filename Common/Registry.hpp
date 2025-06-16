#pragma once

#include "WinApiGeneralException.hpp"
#include "defines.hpp"

#include<filesystem>
#include <Windows.h>

// [CR] Remove New Line!
// [CR] NT_SUCCESS is defined
#define NT_ERROR(Status) ((((ULONG)(Status)) >> 30) == 3)

// [CR] Remove New Line!
class Registry final
{
public:
	explicit Registry(const Registry& parent_key, const std::filesystem::path& registry_path);
	explicit Registry(const std::filesystem::path& registry_path);
	~Registry();

	// [CR] Conventions - ASCII String?
	void write(const std::string& value_name, const std::string& value_conent);
	// [CR] Deffenivness - NODISCARD
	Registry create_key(const std::string& key_name);

	const static Registry REGISTRY_CLASSES_ROOT;
	const static Registry REGISTRY_CURRENT_CONFIG;
	const static Registry REGISTRY_CURRENT_USER;
	const static Registry REGISTRY_LOCAL_MACHINE;
	const static Registry REGISTRY_USERS;


private:
	explicit Registry(HKEY key);
	// [CR] Conventions - whole mess with spaces
	static NODISCARD HKEY open_registry_key(const Registry& base_key ,  const std::filesystem::path& registry_path);

	HKEY m_key;
	bool m_owns_handle;
};

