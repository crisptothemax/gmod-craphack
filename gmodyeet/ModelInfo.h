#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "method.h"
#include "model.h"


class ModelInfo
{
public:
	inline DWORD* GetModel(int index) noexcept
	{
		using GetModel = DWORD * (__thiscall*)(void*, int);
		return method<GetModel>(1, this)(this, index);
	}

	inline int GetModelIndex(const char* name) noexcept
	{
		using GetModelIndex = int(__thiscall*)(void*, const char*);
		return method<GetModelIndex>(2, this)(this, name);
	}

	inline const char* GetModelName(const DWORD* model) noexcept
	{
		using GetModelName = const char* (__thiscall*)(void*, const DWORD*);
		return method<GetModelName>(3, this)(this, model);
	}

	studiohdr_t* GetStudiomodel(const DWORD* mod) noexcept
	{
		using GetStudiomodel = studiohdr_t * (__thiscall*)(void*, const DWORD*);
		return method<GetStudiomodel>(28, this)(this, mod);
	}

};