#pragma once
#include "method.h"


class IPanel
{
public:
	const char* GetName(unsigned int id) noexcept
	{
		using GetName = const char* (__thiscall*)(void*, unsigned int);
		return method<GetName>(36, this)(this, id);
	}

	void SetMouseInputEnabled(unsigned int panel, bool state) noexcept
	{
		using setmouseinput = void(__thiscall*)(void*, int, bool);
		return method<setmouseinput>(32, this)(this, panel, state);
	}

	void SetTopMostPoppup(unsigned int panel, bool state) noexcept
	{
		using SetTopMostPoppup = void(__thiscall*)(void*, unsigned int, bool);
		return method<SetTopMostPoppup>(59, this)(this, panel, state);
	}
};