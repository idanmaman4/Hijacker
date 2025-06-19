#pragma once
#include "DefineWinAPi.hpp"
#include "Defines.hpp"
#include <utility>

class Handle final
{
public:
	explicit Handle(HANDLE raw_handle);
	~Handle();
	Handle(Handle&& handle);
	
	NO_DISCARD HANDLE get_raw_handle();

	Handle(Handle&) = delete;
	Handle& operator=(Handle&) = delete;
	Handle& operator=(Handle&&) = delete;

private:
	HANDLE m_handle;
};
