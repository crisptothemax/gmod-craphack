#pragma once
#include "Panel.h"
#include "Surface.h"
#include "Client.h"
#include "netvarmngr.h"
#include "Engine.h"
#include "EntityList.h"
#include "Globals.h"
#include "ClientMode.h"
#include "ModelInfo.h"
#include "DebugOverlay.h"
#include "GLua.h"

#include <d3d9.h>
#include <d3dx9.h>

#include "Input.h"
#include "Random.h"

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

DWORD dwFindPattern(DWORD dwAddress, DWORD dwLength, const char* szPattern)
{
	const char* pat = szPattern;
	DWORD firstMatch = NULL;
	for (DWORD pCur = dwAddress; pCur < dwLength; pCur++)
	{
		if (!*pat) return firstMatch;
		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
			if (!firstMatch) firstMatch = pCur;
			if (!pat[2]) return firstMatch;
			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
			else pat += 2;
		}
		else {
			pat = szPattern;
			firstMatch = 0;
		}
	}
	return NULL;
}

DWORD GetClientSignature(char* chPattern)
{
	static HMODULE hmModule = GetModuleHandle(L"client.dll");
	static PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hmModule;
	static PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)(((DWORD)hmModule) + pDOSHeader->e_lfanew);
	return dwFindPattern(((DWORD)hmModule) + pNTHeaders->OptionalHeader.BaseOfCode, ((DWORD)hmModule) + pNTHeaders->OptionalHeader.SizeOfCode, chPattern);
}

DWORD GetEngineSignature(char* chPattern)
{
	static HMODULE hmModule = GetModuleHandle(L"engine.dll");
	static PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hmModule;
	static PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)(((DWORD)hmModule) + pDOSHeader->e_lfanew);
	return dwFindPattern(((DWORD)hmModule) + pNTHeaders->OptionalHeader.BaseOfCode, ((DWORD)hmModule) + pNTHeaders->OptionalHeader.SizeOfCode, chPattern);
}

DWORD GetRendererSig(char* chPattern)
{
	static HMODULE hmModule = GetModuleHandle(L"gameoverlayrenderer.dll");
	static PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hmModule;
	static PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)(((DWORD)hmModule) + pDOSHeader->e_lfanew);
	return dwFindPattern(((DWORD)hmModule) + pNTHeaders->OptionalHeader.BaseOfCode, ((DWORD)hmModule) + pNTHeaders->OptionalHeader.SizeOfCode, chPattern);
}

void* CaptureInterface(const char* module_name, const char* interface_name)
{
	auto create_interface_fn = reinterpret_cast<void* (*)(const char* pName, int* pReturnCode)>(GetProcAddress(GetModuleHandleA(module_name), "CreateInterface"));
	return create_interface_fn(interface_name, nullptr);
}



namespace i
{

	CUniformRandomStream* random = nullptr;
	lua::Shared* lua = reinterpret_cast<lua::Shared*>(CaptureInterface("lua_shared.dll", "LUASHARED003"));
	IBaseClient* client = reinterpret_cast<IBaseClient*>(CaptureInterface("client.dll", "VClient017"));
	IClientModeShared* clientmode = reinterpret_cast<IClientModeShared*>(**(IClientModeShared * **)(GetClientSignature((char*)"8B 0D ? ? ? ? 8B 01 FF 50 20 50 8B CB") + 2));
	INetVarManager* netvar = new INetVarManager(client);
	IDebugOverlay* debugoverlay = reinterpret_cast<IDebugOverlay*>(CaptureInterface("engine.dll", "VDebugOverlay003"));
	IPanel* panel = reinterpret_cast<IPanel*>(CaptureInterface("vgui2.dll", "VGUI_Panel009"));
	ModelInfo* modelinfo = reinterpret_cast<ModelInfo*>(CaptureInterface("engine.dll", "VModelInfoClient006"));
	ISurface* surface = reinterpret_cast<ISurface*>(CaptureInterface("vguimatsurface.dll", "VGUI_Surface030"));
	InputSystem* inputSystem = reinterpret_cast<InputSystem*>(CaptureInterface("inputsystem.dll", "InputSystemVersion001"));
	IEntityList* entitylist = reinterpret_cast<IEntityList*>(CaptureInterface("client.dll", "VClientEntityList003"));
	IEngine* engine = reinterpret_cast<IEngine*>(CaptureInterface("engine.dll", "VEngineClient013"));
	CPlayerInfoManager* globals = reinterpret_cast<CPlayerInfoManager*>(CaptureInterface("server.dll", "PlayerInfoManager002"));
}

void cock()
{
	void(*RandomSeed)(int);
	*(void**)& RandomSeed = GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomSeed");
	if (RandomSeed) i::random = **(CUniformRandomStream * **)((uintptr_t)RandomSeed + 0x5);
}


namespace dx
{
	WNDPROC originalWndProc;

	DWORD present = GetRendererSig((char*)"FF 15 ? ? ? ? 8B F8 85 DB") + 2;
	DWORD reset = GetRendererSig((char*)"C7 45 ? ? ? ? ? FF 15 ? ? ? ? 8B F8") + 9;

	std::add_pointer_t<HRESULT __stdcall(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*)> oPresent;
	std::add_pointer_t<HRESULT __stdcall(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*)> oReset;
}