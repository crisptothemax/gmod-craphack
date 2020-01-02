#pragma once
#include "method.h"

class InputSystem
{
public:

	void resetInputState() noexcept
	{
		using resetInputState = void(__thiscall*)(void*);
		return method<resetInputState>(25, this)(this);
	}
};