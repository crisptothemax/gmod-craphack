#pragma once

class IPlayerInfo;

class CGlobals
{
public:
	float realtime;
	int framecount;
	float absoluteframetime;
	float curtime;
	float frametime;
	int maxclients;
	int tickcount;
	float interval_per_tick;
	float interpolation_amount;
	int Shots;
};

class CPlayerInfoManager
{
public:
	virtual IPlayerInfo* GetPlayerInfo(void* pEdict);
	virtual CGlobals* GetGlobalVars();
};