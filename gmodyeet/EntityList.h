#pragma once
#include "method.h"

class IEntityList
{
public:
	inline void* GetClientEntity(int id) noexcept
	{
		using GetClientEntity = void* (__thiscall*)(void*, int);
		return method<GetClientEntity>(3, this)(this, id);
	}

	inline void* GetClientEntityFromHandle(int handle) noexcept
	{
		using GetClientEntityFromHandle = void* (__thiscall*)(void*, int);
		return method<GetClientEntityFromHandle>(4, this)(this, handle);
	}

	inline int GetHighestEntityIndex() noexcept
	{
		using GetHighestEntityIndex = int(__thiscall*)(void*);
		return method<GetHighestEntityIndex>(6, this)(this);
	}
};