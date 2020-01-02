#pragma once
#include <Windows.h>
#include "Vector.h"
#include "method.h"
#include "interfaces.h"

enum classids {
	CTestTraceline = 194,
	CTEWorldDecal = 195,
	CTESpriteSpray = 192,
	CTESprite = 191,
	CTESparks = 190,
	CTESmoke = 189,
	CTEShowLine = 187,
	CTEProjectedDecal = 185,
	CTEPlayerDecal = 184,
	CTEPhysicsProp = 182,
	CTEParticleSystem = 181,
	CTEMuzzleFlash = 180,
	CTELargeFunnel = 178,
	CTEKillPlayerAttachments = 177,
	CTEImpact = 176,
	CTEGlowSprite = 174,
	CTEShatterSurface = 186,
	CTEFootprintDecal = 172,
	CTEFizz = 171,
	CTEExplosion = 170,
	CTEEnergySplash = 169,
	CTEEffectDispatch = 168,
	CTEDynamicLight = 167,
	CTEDecal = 165,
	CTEClientProjectile = 163,
	CTEBubbleTrail = 162,
	CTEBubbles = 161,
	CTEBSPDecal = 160,
	CTEBreakModel = 159,
	CTEBloodStream = 158,
	CTEBloodSprite = 157,
	CTEBeamSpline = 156,
	CTEBeamRingPoint = 155,
	CTEBeamRing = 154,
	CTEBeamPoints = 153,
	CTEBeamLaser = 152,
	CTEBeamFollow = 151,
	CTEBeamEnts = 150,
	CTEBeamEntPoint = 149,
	CTEBaseBeam = 148,
	CTEArmorRicochet = 147,
	CTEMetalSparks = 179,
	CSteamJet = 143,
	CSmokeStack = 138,
	DustTrail = 240,
	CFireTrail = 52,
	SporeTrail = 247,
	SporeExplosion = 246,
	RocketTrail = 244,
	SmokeTrail = 245,
	CPropVehicleDriveable = 123,
	ParticleSmokeGrenade = 243,
	CParticleFire = 99,
	MovieExplosion = 241,
	CTEGaussExplosion = 173,
	CEnvQuadraticBeam = 45,
	CEmbers = 37,
	CEnvWind = 50,
	CPrecipitation = 113,
	CBaseTempEntity = 22,
	NextBotCombatCharacter = 242,
	CWeaponStunStick = 236,
	CWeaponSMG1 = 234,
	CWeapon_SLAM = 204,
	CWeaponShotgun = 232,
	CWeaponRPG = 229,
	CLaserDot = 84,
	CWeaponPistol = 228,
	CWeaponPhysCannon = 226,
	CBaseHL2MPCombatWeapon = 16,
	CBaseHL2MPBludgeonWeapon = 15,
	CHL2MPMachineGun = 76,
	CWeaponHL2MPBase = 223,
	CWeaponFrag = 218,
	CWeaponCrowbar = 213,
	CWeaponCrossbow = 211,
	CWeaponAR2 = 207,
	CWeapon357 = 202,
	CHL2MPGameRulesProxy = 75,
	CTEHL2MPFireBullets = 175,
	CTEPlayerAnimEvent = 183,
	CHL2MPRagdoll = 77,
	CHL2MP_Player = 74,
	CCrossbowBolt = 34,
	CWeaponHopwire = 0,
	CWeaponOldManHarpoon = 225,
	CWeaponCitizenSuitcase = 210,
	CWeaponCitizenPackage = 209,
	CWeaponAlyxGun = 205,
	CWeaponCubemap = 215,
	CWeaponGaussGun = 0,
	CWeaponAnnabelle = 206,
	CFlaregun = 0,
	CWeaponBugBait = 208,
	CWeaponBinoculars = 0,
	CWeaponCycler = 216,
	CVortigauntEffectDispel = 198,
	CVortigauntChargeToken = 197,
	CNPC_Vortigaunt = 98,
	CPropVehiclePrisonerPod = 124,
	CPropCrane = 117,
	CPropCannon = 0,
	CPropAirboat = 115,
	CFlare = 54,
	CTEConcussiveExplosion = 164,
	CNPC_Strider = 97,
	CScriptIntro = 132,
	CRotorWashEmitter = 129,
	CPropCombineBall = 116,
	CPlasmaBeamNode = 0,
	CNPC_RollerMine = 96,
	CNPC_Manhack = 94,
	CNPC_CombineGunship = 93,
	CNPC_AntlionGuard = 90,
	CInfoTeleporterCountdown = 83,
	CMortarShell = 89,
	CEnvStarfield = 48,
	CEnvHeadcrabCanister = 42,
	CAlyxEmpEffect = 2,
	CCorpse = 33,
	CCitadelEnergyCore = 30,
	CHL2_Player = 73,
	CBaseHLBludgeonWeapon = 17,
	CHLSelectFireMachineGun = 79,
	CHLMachineGun = 78,
	CBaseHelicopter = 11,
	CNPC_Barney = 92,
	CNPC_Barnacle = 91,
	AR2Explosion = 0,
	CTEAntlionDust = 146,
	CBaseHLCombatWeapon = 18,
	CWeaponShotgun_HL1 = 233,
	CWeaponSatchel = 231,
	CWeaponRPG_HL1 = 230,
	CLaserDot_HL1 = 85,
	CWeaponMP5 = 224,
	CWeaponHgun = 222,
	CWeaponHandGrenade = 221,
	CWeaponGlock = 220,
	CWeaponGauss = 219,
	CWeaponEgon = 217,
	CWeaponCrossbow_HL1 = 212,
	CWeapon357_HL1 = 203,
	CBaseHL1MPCombatWeapon = 14,
	CWeaponTripMine = 238,
	CWeaponSnark = 235,
	CWeaponCrowbar_HL1 = 214,
	CBaseHelicopter_HL1 = 12,
	CRpgRocket = 130,
	CBaseHL1CombatWeapon = 13,
	CBeamSpotlight = 25,
	CGMOD_Player = 70,
	CFleshEffectTarget = 55,
	CPropJeepEpisodic = 120,
	CPropScalable = 121,
	CNPC_Puppet = 95,
	CHandleTest = 72,
	CSpriteTrail = 142,
	CSpriteOriented = 141,
	CSprite = 140,
	CRagdollPropAttached = 127,
	CRagdollProp = 126,
	CPredictedViewModel = 114,
	CPoseController = 112,
	CGameRulesProxy = 69,
	CInfoLadderDismount = 80,
	CFuncLadder = 62,
	CEnvDetailController = 41,
	CWorld = 239,
	CWaterLODControl = 201,
	CWaterBullet = 200,
	CVoteController = 199,
	CVGuiScreen = 196,
	CPropJeep = 119,
	CPropVehicleChoreoGeneric = 122,
	CTest_ProxyToggle_Networkable = 193,
	CTesla = 188,
	CTeam = 145,
	CSun = 144,
	CParticlePerformanceMonitor = 100,
	CSpotlightEnd = 139,
	CSlideshowDisplay = 137,
	CShadowControl = 136,
	CSceneEntity = 131,
	CRopeKeyframe = 128,
	CRagdollManager = 125,
	CPhysicsPropMultiplayer = 106,
	CPhysBoxMultiplayer = 104,
	CPropDoorRotating = 118,
	CBasePropDoor = 21,
	CDynamicProp = 36,
	CPointCommentaryNode = 111,
	CPointCamera = 110,
	CPlayerResource = 109,
	CPlasma = 108,
	CPhysMagnet = 107,
	CPhysicsProp = 105,
	CPhysBox = 103,
	CParticleSystem = 101,
	CMaterialModifyControl = 88,
	CLightGlow = 86,
	CInfoOverlayAccessor = 82,
	CFuncTrackTrain = 68,
	CFuncSmokeVolume = 67,
	CFuncRotating = 66,
	CFuncReflectiveGlass = 65,
	CFuncOccluder = 64,
	CFuncMonitor = 63,
	CFunc_LOD = 59,
	CTEDust = 166,
	CFunc_Dust = 58,
	CFuncConveyor = 61,
	CBreakableSurface = 29,
	CFuncAreaPortalWindow = 60,
	CFish = 53,
	CEntityFlame = 39,
	CFireSmoke = 51,
	CEnvTonemapController = 49,
	CEnvScreenEffect = 46,
	CEnvScreenOverlay = 47,
	CEnvProjectedTexture = 44,
	CEnvParticleScript = 43,
	CFogController = 57,
	CEntityParticleTrail = 40,
	CEntityDissolve = 38,
	CDynamicLight = 35,
	CColorCorrectionVolume = 32,
	CColorCorrection = 31,
	CBreakableProp = 28,
	CBasePlayer = 20,
	CBaseFlex = 9,
	CBaseEntityy = 8,
	CBaseDoor = 7,
	CBaseCombatCharacter = 5,
	CBaseAnimatingOverlay = 4,
	CBoneFollower = 26,
	CBaseAnimating = 3,
	CInfoLightingRelative = 81,
	CAI_BaseNPC = 1,
	CBeam = 24,
	CBaseViewModel = 23,
	CBaseParticleEntity = 19,
	CBaseGrenade = 10,
	CBaseCombatWeapon = 6,
	CWeaponPhysGun = 227,
	CPhysBeam = 102,
	CLuaNextBot = 87,
	CFlexManipulate = 56,
	CBoneManipulate = 27,
	CWeaponSWEP = 237,
	CSENT_point = 135,
	CSENT_anim = 134,
	CSENT_AI = 133,
	CGMODGameRulesProxy = 71,
}classids;


struct string
{
	char data[64];
};

enum lifestates
{
	LIFE_ALIVE = 0,
	LIFE_DEAD = 2,
};

void VectorTransform(const Vector& vSome, const matrix3x4_t& vMatrix, Vector& vOut) noexcept
{
	for (auto i = 0; i < 3; i++)
		vOut[i] = vSome.Dot((Vector&)vMatrix[i]) + vMatrix[i][3];
}

class lua_stack
{
public:
	lua_stack() {
		m_lua = nullptr;
		m_top = -1;
	}
	lua_stack(lua::ILua* lua) : m_lua{ lua }, m_top{ m_lua->Top() } { }

	~lua_stack() {
		m_lua->Pop(m_lua->Top() - m_top);
	}

	using size_type  = std::int32_t;
	using value_type = lua::ILua*;
private:
	value_type m_lua;
	size_type  m_top;
public:
	value_type operator->() noexcept {
		return m_lua;
	}
	bool operator!() noexcept {
		return m_lua == nullptr;
	}
};

struct harray
{
	int a[16];
};

struct str
{
	char n[32];
};

class CBaseEntity
{
public:
	int& m_nTickBase()
	{
		return *(int*)((uintptr_t)this + 0x2588);
	}

	float get_fas2_cone()
	{
		auto glua = i::lua->create_interface(lua::type::client);

		if (!glua)
			return 0.f;

		glua->PushSpecial(lua::special::glob); // 1
		glua->GetField(-1, "LocalPlayer"); // 2
		glua->Call(0, 1); // 2 - 1 = 1 + 1 = 2

		glua->GetField(-1, "GetActiveWeapon"); // 3
		glua->Push(-2); // 4
		glua->Call(1, 1); // 4 - 2 = 2 + 1 = 3

		glua->GetField(-1, "CurCone"); // 4
		if (!glua->IsType(-1, lua::NUMBER))
		{
			glua->Pop(3);
			return -1.0f;
		}

		float cone = (float)glua->GetNumber(-1);

		glua->Pop(4);

		return cone;
	}

	void RandomSeed(float seed)
	{
		auto glua = i::lua->create_interface(lua::type::client);

		if (!glua)
			return;

		glua->PushSpecial(lua::special::glob); // 1
		glua->GetField(-1, "math"); // 2
		glua->GetField(-1, "randomseed"); // 3
		glua->PushNumber(seed); // 4
		glua->Call(1, 0); // 4 - 2 = 2 + 0 = 2

		glua->Pop(2);
	}

	float Rand(float min, float max)
	{
		auto glua = i::lua->create_interface(lua::type::client);

		if (!glua)
			return 0.f;

		glua->PushSpecial(lua::special::glob); // 1
		glua->GetField(-1, "math"); // 2
		glua->GetField(-1, "Rand"); // 3
		glua->PushNumber(min); // 4
		glua->PushNumber(max); // 5
		glua->Call(2, 1); // 5 - 3 = 2 + 1 = 3

		float randfloat = (float)glua->GetNumber(-1);
		glua->Pop(3);

		return randfloat;
	}

	bool UsesLua()
	{
		using UsesLua = bool(__thiscall*)(void*);
		return method<UsesLua>(170, this)(this);
	}

	float LUASpread()
	{
		if (!this->UsesLua())
			return -1.0f;

		auto Lua = i::lua->create_interface(lua::type::client);

		this->PushEntity();
		Lua->GetField(-1, "Primary");
		if (!Lua->IsType(-1, lua::TABLE))
		{
			Lua->Pop(2);
			return -1.0f;
		}
		Lua->GetField(-1, "Spread");
		if (!Lua->IsType(-1, lua::NUMBER))
		{
			Lua->Pop(3);
			return -1.0f;
		}
		double out = Lua->GetNumber(-1);
		Lua->Pop(3);
		return out;
	}

	float LUASpread2()
	{
		if (!this->UsesLua())
			return -1.0f;

		auto Lua = i::lua->create_interface(lua::type::client);

		this->PushEntity();
		Lua->GetField(-1, "Spread");
		if (!Lua->IsType(-1, lua::NUMBER))
		{
			Lua->Pop(2);
			return -1.0f;
		}
		double out = Lua->GetNumber(-1);
		Lua->Pop(2);
		return out;
	}

	float TTTSpread()
	{
		if (!this->UsesLua())
			return -1.0f;

		auto Lua = i::lua->create_interface(lua::type::client);

		this->PushEntity();
		Lua->GetField(-1, "Primary");
		if (!Lua->IsType(-1, lua::TABLE))
		{
			Lua->Pop(2);
			return -1.0f;
		}
		Lua->GetField(-1, "Cone");
		if (!Lua->IsType(-1, lua::NUMBER))
		{
			Lua->Pop(3);
			return -1.0f;
		}
		double out = Lua->GetNumber(-1);
		Lua->Pop(3);
		return out;
	}

	bool HasPrimaryAmmo()
	{
		using HasPrimaryAmmo = bool(__thiscall*)(void*);
		return method<HasPrimaryAmmo>(27, this)(this);
	}

	bool CanShoot()
	{
		if (!this)
			return false;

		if ((this->m_flNextPrimaryAttack() <= i::globals->GetGlobalVars()->curtime) && (this->HasPrimaryAmmo()))
			return true;

		return false;
	}

	float m_flNextPrimaryAttack()
	{
		if (this == nullptr)
			return 0.0f;
		return *reinterpret_cast<float*>((DWORD)this + 0x17CC);
	}

	Vector GetBulletSpread()
	{
		if (this == nullptr)
			return Vector(0, 0, 0);

		if (this->UsesLua())
		{
			float LUASpreadCone = this->LUASpread();
			if (!strcmp(this->GetWeaponBase(), "weapon_tttbase"))
				LUASpreadCone = this->TTTSpread();

			if (LUASpreadCone != -1.0f)
				return Vector(LUASpreadCone, LUASpreadCone, LUASpreadCone);

			LUASpreadCone = this->LUASpread2();
			if (LUASpreadCone != -1.0f)
				return Vector(LUASpreadCone, LUASpreadCone, LUASpreadCone);
		}

		return this->orgGetBulletSpread();
	}

	const Vector& orgGetBulletSpread()
	{
		using orgGetBulletSpread = const Vector&(__thiscall*)(void*);
		return method<orgGetBulletSpread>(170, this)(this);
	}

	const char* GetWeaponBase()
	{

		auto Lua = i::lua->create_interface(lua::type::client);

		this->PushEntity();
		Lua->GetField(-1, "Base");
		if (!Lua->IsType(-1, lua::STRING))
		{
			Lua->Pop(2);
			return "";
		}
		const char* out = Lua->GetString(-1);
		Lua->Pop(2);
		return out;
	}

	bool IsWeapon()
	{
		using IsWeapon = bool(__thiscall*)(void*);
		return method<IsWeapon>(167, this)(this);
	}

	int m_iParentAttachment()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x17a);
	}

	int m_iGModFlags()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x644);
	}

	int m_nRenderMode()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x7c);
	}

	Color m_clrRender()
	{
		return *reinterpret_cast<Color*>((DWORD)this + 0x58);
	}

	str GetScriptName()
	{
		return *reinterpret_cast<str*>((DWORD)this + 0xB40);
	}

	harray GetAllWeapons()
	{
		//m_hMyWeapons
		return *reinterpret_cast<harray*>((DWORD)this + 0x1E10);
	}
	
	void PushEntity()
	{
		using pushent = void(__thiscall*)(void*);
		return method<pushent>(172,this)(this);
	}

	const char* GetEntityName()
	{
		auto glua = i::lua->create_interface(lua::type::client);

		lua_stack lua(glua);

		if (!lua)
			return "-1";

		lua->PushSpecial(lua::special::glob);
		lua->GetField(-1, "Entity");
		lua->PushNumber(this->GetIndex());
		lua->Call(1, 1);
		lua->GetField(-1, "GetName");
		lua->Push(-2);
		lua->Call(1, 1);

		return lua->GetString(-1);

	}

	inline const char* GetWeaponNameInternal()
	{
		using GetWeaponName =  const char* (__thiscall*)(void*);
		return method<GetWeaponName>(366, this)(this);
	}

	const char* GetWeaponName()
	{
		auto glua = i::lua->create_interface(lua::type::client);

		lua_stack lua(glua);

		if (!lua)
			return "";

		PushEntity();

		
		if (!lua->IsType(-1, lua::ENTITY)) {
			return "";
		}

		lua->GetField(-1, "PrintName");
		if (!lua->IsType(-1, lua::STRING))
			return "";

		return lua->GetString(-1);
	}

	const char* GetEntName()
	{
		auto glua = i::lua->create_interface(lua::type::client);

		lua_stack lua(glua);

		if (!lua)
			return "";

		PushEntity();


		if (!lua->IsType(-1, lua::ENTITY)) {
			return "";
		}

		lua->GetField(-1, "Name");
		if (!lua->IsType(-1, lua::STRING))
			return "";

		return lua->GetString(-1);
	}

	int GetClipFirst()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x1818);
	}

	int GetClipSecond()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x181C);
	}

	int GetWeaponState()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x1808);
	}

	int GetWeaponOwner()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x17C8);
	}

	double GetClip1()
	{
		auto glua = i::lua->create_interface(lua::type::client);

		lua_stack lua(glua);

		if (!lua)
			return -1;

		PushEntity();

		if (!lua->IsType(-1, lua::ENTITY)) {
			return -2;
		}

		lua->GetField(-1, "Clip1");

		lua->Call(0, 1);

		if (!lua->IsType(-1, lua::NUMBER))
			return -3;

		return lua->GetNumber(-1);
	}


	bool isadmin()
	{
		auto glua = i::lua->create_interface(lua::type::client);

		if (!glua) return {};

		glua->PushSpecial(lua::special::glob);
		glua->GetField(-1, "Entity");
		glua->PushNumber(GetIndex());
		glua->Call(1, 1);

		glua->GetField(-1,"IsAdmin");
		glua->Push(-2);
		glua->Call(1, 1);

		bool admin = glua->GetBool();
		
		glua->Pop(3);

		return admin;
	}

	Color getteamcolor()
	{
		auto glua = i::lua->create_interface(lua::type::client);

		if (!glua)
			return {};

		glua->PushSpecial(lua::special::glob); //1
		glua->GetField(-1, "team"); //2
		glua->GetField(-1, "GetColor");//3
		glua->PushNumber(this->GetTeamNum());//4
		glua->Call(1, 1);//4-2 = 2 + 1 = 3

		glua->PushString("r"); //4
		glua->GetTable(-2);//
		auto r = glua->GetNumber(-1);
		glua->Pop();

		glua->PushString("g");
		glua->GetTable(-2);
		auto g = glua->GetNumber(-1);
		glua->Pop();

		glua->PushString("b");
		glua->GetTable(-2);
		auto b = glua->GetNumber(-1);
		glua->Pop(3);

		return { (int)r,(int)g,(int)b,255 };
	}


	bool IsAlive()
	{
		return GetHealth() > 0 && GetLifestate() == LIFE_ALIVE;
		
	}

	Vector angrot()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0x2BE4);
	}

	void GetRenderBounds(Vector& mins, Vector& maxs)
	{
		if ((DWORD)this == 0) return;

		void* pRenderable = (void*)(this + 0x4);
		using GetRenderBounds = void(__thiscall*)(void*, Vector&, Vector&);
		return method<GetRenderBounds>(20, pRenderable)(pRenderable, mins, maxs);
	}

	inline size_t GetIndex()
	{
		void* networkable = this + 8;
		using get_entity_index_t = size_t(__thiscall*)(PVOID);
		return method<get_entity_index_t>(9, networkable)(networkable);
	}

	const Vector& GetMins()
	{
		void* pCol = GetCollideable();
		if (pCol)
		{
			using getmins = const Vector& (__thiscall*)(void*);
			return method<getmins>(3, pCol)(pCol);
		}
	}

	const Vector& GetMaxs()
	{
		void* pCol = GetCollideable();
		if (pCol)
		{
			using getmaxs = const Vector& (__thiscall*)(void*);
			return method<getmaxs>(4, pCol)(pCol);
		}
	}

	bool SetupBones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) noexcept
	{
		if ((DWORD)this == 0) return false;
		PVOID pRenderable = (PVOID)(this + 0x4);
		using setup_bones = bool(__thiscall*)(PVOID, matrix3x4_t*, int, int, float);
		return method<setup_bones>(16, pRenderable)(pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}


	inline Vector get_bone_pos(int bone, float time) noexcept
	{
		static matrix3x4_t boneMatrices[128];
		if (SetupBones(boneMatrices, 128, 256, time))
			return Vector{ boneMatrices[bone][0][3],boneMatrices[bone][1][3], boneMatrices[bone][2][3] };
		else
			return Vector{ 0,0,0 };
	}

	ClientClass* GetClientClass() noexcept
	{
		PVOID pNetworkable = (PVOID)(this + 0x8);
		using getclass = ClientClass * (__thiscall*)(PVOID);
		return method<getclass>(2, pNetworkable)(pNetworkable);
	}

	DWORD* GetModel() noexcept
	{
		if ((DWORD)this == 0) return 0;
		PVOID pRenderable = (PVOID)(this + 0x4);
		using getmodel = DWORD * (__thiscall*)(PVOID);
		return method<getmodel>(9, pRenderable)(pRenderable);
	}

	inline bool IsDormant() noexcept
	{
		if ((DWORD)this == 0) return true;
		void* pnetworkable = this + 8;
		using IsDormant = bool(__thiscall*)(PVOID);
		return method<IsDormant>(8, pnetworkable)(pnetworkable);
	}

	const Vector& GetRenderOrigin() noexcept
	{
		if ((DWORD)this == 0) return { 0,0,0 };
		PVOID pRenderable = (PVOID)(this + 0x4);
		using getmodel = const Vector& (__thiscall*)(PVOID);
		return method<getmodel>(1, pRenderable)(pRenderable);
	}

	const Vector& GetRenderAngles() noexcept
	{
		if ((DWORD)this == 0) return { 0,0,0 };
		PVOID pRenderable = (PVOID)(this + 0x4);
		using getmodel = const Vector& (__thiscall*)(PVOID);
		return method<getmodel>(2, pRenderable)(pRenderable);
	}

	Vector GetHitboxPosition(int iHitbox, ModelInfo* m, float currtime) noexcept
	{
		DWORD* model = GetModel();
		if (!model)
			return Vector();

		studiohdr_t* hdr = m->GetStudiomodel(model);

		if (!hdr)
			return Vector();

		matrix3x4_t matrix[128];
		if (!SetupBones(matrix, 128, 0x100, currtime))
			return Vector();

		mstudiohitboxset_t* set = hdr->GetHitboxSet(GetHitboxSet());
		if (!set)
			return Vector();

		mstudiobbox_t* box = set->pHitbox(iHitbox);
		if (!box)
			return Vector();

		Vector center = (box->bbmin + box->bbmax) * 0.5f;

		Vector vHitbox;

		VectorTransform(center, matrix[box->bone], vHitbox);

		return vHitbox;
	}

	void* GetCollideable()
	{
		using retard = void* (__thiscall*)(void*);
		return method<retard>(3, this)(this);
	}

	int GetHealth()
	{
		if ((DWORD)this == 0 )return 0;
		return *reinterpret_cast<int*>((DWORD)this + 0x90);
	}

	Vector GetViewOffset()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0xE8);
	}

	int GetMaxHealth()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x94);
	}

	BYTE GetLifestate()
	{
		return *reinterpret_cast<BYTE*>((DWORD)this + 0x8F);
	}

	int GetFlags()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x350);
	}

	Vector GetOrigin()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0x338);
	}

	Vector GetAngRotation()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0x344);
	}

	int GetTeamNum()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x9C);
	}

	bool IsOnFire()
	{
		return *reinterpret_cast<bool*>((DWORD)this + 0x515);
	}

	Vector GetVelocity()
	{
		return *reinterpret_cast<Vector*>((DWORD)this + 0xF4);
	}

	int GetHitboxSet()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x1398);
	}

	int GetActiveWeaponHandle()
	{
		//m_hActiveWeapon
		return *reinterpret_cast<int*>((DWORD)this + 0x2210);
	}

	//DT_GMOD_Player
	bool IsTyping()
	{
		return *reinterpret_cast<bool*>((DWORD)this + 0x2DB2);
	}

	//DT_PlayerReeeeesource
	int GetPing()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x1590);
	}

	int GetScore()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x1794);
	}

	int GetDeaths()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x1998);
	}

	int IsConnected()
	{
		return *reinterpret_cast<bool*>((DWORD)this + 0x1B9C);
	}

	bool IsAlive2()
	{
		return *reinterpret_cast<bool*>((DWORD)this + 0x1E24);
	}

	int GetHealth2()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x1EA8);
	}
	//not working
	int GetArmor()
	{
		return *reinterpret_cast<int*>((DWORD)this + 0x20AC);
	}

	//DT_Team not sure
	string GetTeamName()
	{
		return *reinterpret_cast<string*>((DWORD)this + 0x139c);
	}
};