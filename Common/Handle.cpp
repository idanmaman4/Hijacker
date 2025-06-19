#include "Handle.hpp"

Handle::Handle(HANDLE raw_handle) : m_handle(raw_handle)
{
}

Handle::~Handle()
{
	try{
		if (m_handle != INVALID_HANDLE_VALUE) {
			CloseHandle(m_handle);
		}
	}
	catch (...) {
	}
}

Handle::Handle(Handle&& handle) : m_handle(std::exchange(handle.m_handle, INVALID_HANDLE_VALUE))
{
}

NO_DISCARD HANDLE Handle::get_raw_handle()
{
	return m_handle;
}
