#pragma once
#include "method.h"
#include <stdint.h>
#include "vector.h"

using matrix4x4_t = float[16];
using matrix3x4_t = float[3][4];

struct player_info_t
{
	char name[128];
	int  id;
	char guid[33];
	struct
	{
		uint32_t id;
		char name[128];
	} buddy;
	bool bot;
	bool hltv;
	uint32_t files[4];
	uint8_t  downloaded;
};

class IEngine
{

public:
	inline size_t get_local_player() noexcept
	{
		using get_local_player_t = size_t(__thiscall*)(void*);
		return method<get_local_player_t>(12, this)(this);
	}

	inline bool get_player_info(size_t index, player_info_t* info) noexcept
	{
		using get_player_info_t = bool(__thiscall*)(void*, size_t, player_info_t*);
		return method<get_player_info_t>(8, this)(this, index, info);
	}

	inline const matrix3x4_t& get_view_matrix() noexcept
	{
		using get_view_matrix_t = const matrix3x4_t& (__thiscall*)(void*);
		return method<get_view_matrix_t>(36, this)(this);
	}

	inline size_t get_max_clients() noexcept
	{
		using get_max_clients_t = size_t(__thiscall*)(void*);
		return method<get_max_clients_t>(21, this)(this);
	}

	inline void get_screen_size(int& width, int& height) noexcept
	{
		using get_screen_size_t = void(__thiscall*)(void*, int&, int&);
		return method<get_screen_size_t>(5, this)(this, width, height);
	}

	inline void get_view_angles(Vector& Angles) noexcept
	{
		using  get_view_angles = void(__thiscall*)(void*, Vector & Angles);
		return method<get_view_angles>(19, this)(this, Angles);
	}

	inline void set_view_angles(Vector& Angles) noexcept
	{
		using  set_view_angles_t = void(__thiscall*)(void*, Vector & Angles);
		return method<set_view_angles_t>(20, this)(this, Angles);
	}

	inline bool is_ingame() noexcept
	{
		using is_ingame_t = bool(__thiscall*)(void*);
		return method<is_ingame_t>(26, this)(this);
	}

	void ClientCmd(const char* szCommandString) noexcept
	{
		using clcmd = void(__thiscall*)(void*, const char*);
		return method<clcmd>(7, this)(this, szCommandString);
	}

	int GetAppId() noexcept
	{
		using getappid = int(__thiscall*)(void*);
		return method<getappid>(104, this)(this);
	}

	void ClientCmd_Unrestricted(const char* chCommandString) noexcept
	{
		using clcmdunres = void(__thiscall*)(void*, const char*);
		return method<clcmdunres>(106, this)(this, chCommandString);
	}
};