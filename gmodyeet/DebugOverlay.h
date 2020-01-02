#pragma once
#include "method.h"
#include "Vector.h"

class IDebugOverlay
{
public:
	void AddSweptBoxOverlay(const Vector& start, const Vector& end, const Vector& mins, const Vector& max, const Vector& angles, int r, int g, int b, int a, float flDuration)
	{
		using AddSweptBoxOverlay = void(__thiscall*)(void*,const Vector&, const Vector&, const Vector&, const Vector&, const Vector&, int, int, int, int, float);
		return method<AddSweptBoxOverlay>(7, this)(this,start, end, mins, max, angles, r, g, b, a, flDuration);
	}
};