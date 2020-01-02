#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include "vmt.h"
#include "interfaces.h"
#include "CBaseEntity.h"

#include <d3d9.h>
#include <d3dx9.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

#include "config.h"
#include <string>
#include <intrin.h>

#include "checksum_md5.h"


float SpreadAngles;

inline float FloatNegate(float f)
{
	return -f;
}

Vector GetAngle(Vector source, Vector target)
{
	Vector OutputAngle;
	Vector ass = target - source;
	VectorAngles(ass, OutputAngle);
	return OutputAngle;
}

float AngleNormalizez(float angle)
{
	angle = fmodf(angle, 360.0f);
	if (angle > 180)
	{
		angle -= 360;
	}
	if (angle < -180)
	{
		angle += 360;
	}
	return angle;
}

Vector FixAngles(Vector angles)
{
	angles.x = AngleNormalizez(angles.x);
	angles.y = AngleNormalizez(angles.y);
	if (angles.x > 89.f)
		angles.x = 89.f;
	else if (angles.x < -89.f)
		angles.x = -89.f;
	return angles;
}

inline void NormalizeAngle(float& flAngle)
{
	while (flAngle > 180.f)
		flAngle -= 360.f;

	while (flAngle < -180.f)
		flAngle += 360.f;
}

inline void NormalizeAngles(Vector& vecAngles)
{
	for (int iAxis = 0; iAxis < 3; iAxis++)
		NormalizeAngle(vecAngles[iAxis]);
}

Vector SpreadAngle(CUserCmd* cmd,CBaseEntity* wep)
{
	CBaseEntity* LocalPlayer = (CBaseEntity*)i::entitylist->GetClientEntity(i::engine->get_local_player());

	Vector SpreadCone = wep->GetBulletSpread();
	float Spread = FloatNegate(( SpreadCone.x + SpreadCone.y + SpreadCone.z) / 3);

	float Random[2];
	unsigned int seed = MD5_PseudoRandom(cmd->command_number) & 0xFF;
	i::random->SetSeed(seed);

	Random[0] = i::random->RandomFloat(-0.5f, 0.5f) + i::random->RandomFloat(-0.5f, 0.5f);
	Random[1] = i::random->RandomFloat(-0.5f, 0.5f) + i::random->RandomFloat(-0.5f, 0.5f);


	Vector forward, right, up;

	NormalizeAngles(cmd->viewangles);
	AngleVectors(cmd->viewangles, &forward, &right, &up);

	Vector new_va = forward + (right * SpreadCone.x * Random[0] * -1) + (up * SpreadCone.y * Random[1] * -1);
	new_va.NormalizeInPlace();

	Vector ref;

	VectorAngles(new_va, cmd->viewangles);
	NormalizeAngles(ref);

	return ref;
	//Vector ShootDirection = Vector(1.0f, 0.0f, 0.0f) + (Vector(0.0f, -1.0f, 0.0f) * Spread * Random[0]) + (Vector(0.0f, 0.0f, 1.0f) * Spread * Random[1]); // 0,0,0

	//Vector out = GetAngle({ 0,0,0 }, ShootDirection);
	//out = FixAngles(out);
	//return out;
}

static bool ScreenTransform(const Vector& point, Vector& screen) noexcept
{
	const matrix3x4_t& w2sMatrix = i::engine->get_view_matrix();
	screen.x = w2sMatrix[0][0] * point.x + w2sMatrix[0][1] * point.y + w2sMatrix[0][2] * point.z + w2sMatrix[0][3];
	screen.y = w2sMatrix[1][0] * point.x + w2sMatrix[1][1] * point.y + w2sMatrix[1][2] * point.z + w2sMatrix[1][3];
	screen.z = 0.0f;

	float w = w2sMatrix[3][0] * point.x + w2sMatrix[3][1] * point.y + w2sMatrix[3][2] * point.z + w2sMatrix[3][3];

	if (w < 0.001f) {
		screen.x *= 100000;
		screen.y *= 100000;
		return true;
	}

	float invw = 1.0f / w;
	screen.x *= invw;
	screen.y *= invw;

	return false;
}

bool WorldToScreen(const Vector& origin, Vector& screen) noexcept
{
	static int h, w;
	i::engine->get_screen_size(w, h);

	if (!ScreenTransform(origin, screen)) {
		screen.x = (w / 2.0f) + (screen.x * w) / 2;
		screen.y = (h / 2.0f) - (screen.y * h) / 2;

		return true;
	}
	return false;
}

struct ESPBox
{
	Vector flb, brt, blb, frt, frb, brb, blt, flt;
};

void r(Vector& point, Vector angle)
{
	static float _x, _y, _z;
	_x = point.x;
	_y = point.y;
	_z = point.z;

	static float cp, cy, cr;
	static float sp, sy, sr;

	angle.x = Deg2Rad(angle.x);
	angle.y = Deg2Rad(angle.y);
	angle.z = Deg2Rad(angle.z);

	cp = cos(angle.x);
	cy = cos(angle.y);
	cr = cos(angle.z);

	sp = sin(angle.x);
	sy = sin(angle.y);
	sr = sin(angle.z);


	point.x = _x * cy * cp + _y * (cy * sp * sr - sy * cr) + _z * (cy * sp * cr + sy * sr);
	point.y = _x * sy * cp + _y * (sy * sp * sr + cy * cr) + _z * (sy * sp * cr - cy * sr);
	point.z = _y * (cp * sr) + _z * (cp * cr) - sp * _x;
}

Vector org;
Vector ap, bp, cp, dp;
Vector ra, rb, rc, rd;
double rot = 0;
float rotation = 0;
bool button = false;

void Draw()
{
	static Vector sa, sb, sc, sd,sorigin;
	if (WorldToScreen(ra, sa) && WorldToScreen(rb, sb) && WorldToScreen(rc, sc) && WorldToScreen(rd, sd) && WorldToScreen(org,sorigin))
	{
		i::surface->DrawLine(sa.x, sa.y, sb.x, sb.y);
		i::surface->DrawLine(sb.x, sb.y, sc.x, sc.y);
		i::surface->DrawLine(sc.x, sc.y, sd.x, sd.y);
		i::surface->DrawLine(sd.x, sd.y, sa.x, sa.y);

		i::surface->DrawLine(sa.x, sa.y, sc.x, sc.y);
		i::surface->DrawLine(sd.x, sd.y, sb.x, sb.y);

		i::surface->draw_string(fonts::Arial, sa.x, sa.y, colors::green, "A");
		i::surface->draw_string(fonts::Arial, sb.x, sb.y, colors::green, "B");
		i::surface->draw_string(fonts::Arial, sc.x, sc.y, colors::green, "C");
		i::surface->draw_string(fonts::Arial, sd.x, sd.y, colors::green, "D");
	}
}

bool GetBox(CBaseEntity* pEntity, ESPBox& result)
{
	// Variables
	Vector  vOrigin, min, max, sMin, sMax, sOrigin,vAngle;

	// Get the locations
	vOrigin = pEntity->GetRenderOrigin();
	vAngle = pEntity->GetRenderAngles();

	min = pEntity->GetMins();
	max = pEntity->GetMaxs();


	// Points of a 3d bounding box
	Vector points[] = { Vector{min.x, min.y, min.z},
		Vector{min.x, max.y, min.z},
		Vector{max.x, max.y, min.z},
		Vector{max.x, min.y, min.z},

		Vector{max.x, max.y, max.z},
		Vector{min.x, max.y, max.z},
		Vector{min.x, min.y, max.z},
		Vector{max.x, min.y, max.z} };


	for (int i = 0; i <= 7; ++i)
	{
		r(points[i], vAngle);
	}


	// Get screen positions
	if (!WorldToScreen(vOrigin + points[3], result.flb) || !WorldToScreen(vOrigin + points[5], result.brt)
		|| !WorldToScreen(vOrigin + points[0], result.blb) || !WorldToScreen(vOrigin + points[4], result.frt)
		|| !WorldToScreen(vOrigin + points[2], result.frb) || !WorldToScreen(vOrigin + points[1], result.brb)
		|| !WorldToScreen(vOrigin + points[6], result.blt) || !WorldToScreen(vOrigin + points[7], result.flt))
		return false;

	return true;
}

constexpr auto windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
| ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

VMTHook* v_panel = nullptr;
VMTHook* v_clientmode = nullptr;
VMTHook* v_client = nullptr;



void DumpClassIds()
{
	printf("dumping classids..\n");

	std::ofstream output;
	output.open("classiddump.txt");

	output << "enum classids {" << std::endl;
	for (ClientClass* pClass = i::client->GetAllClasses(); pClass; pClass = pClass->pNextClass)
		output << "    " << pClass->chName << " = " << pClass->iClassID << "," << std::endl;
	output << "}classids;" << std::endl;

	output.close();

	printf("dumped classids!\n");
}

void Rotate2DRadar(Vector& point,float angle)
{
	angle = Deg2Rad(angle + 180);
	static float x, y;
	x = (point.y * cos(angle)) - (point.x * sin(angle));
	y = (point.x * cos(angle)) + (point.y * sin(angle));
	point.x = x;
	point.y = y;
}

int radarsz = 200;

bool DrawOnRadar(CBaseEntity* l, CBaseEntity* e, Vector center, const char* text,Color clr)
{
	if ((DWORD)l < 100) return false;
	static Vector lpos, epos, transformed,Angles;
	static int size = 4;
	lpos = l->GetOrigin();
	epos = e->GetOrigin();
	i::engine->get_view_angles(Angles);

	transformed = epos - lpos;
	transformed *= c::radar::zoom;

	Rotate2DRadar(transformed, Angles.y);

	transformed.y *= -1;

	static bool clamped;
	clamped = false;
	//clamping so it wont draw outside radar bounds
	if (transformed.x < 0) {
		if (transformed.x < -radarsz) transformed.x = -radarsz;
		clamped = 1;
	}
	else {
		if (transformed.x > radarsz) transformed.x = radarsz;
		clamped = 1;
	}

	if (transformed.y < 0) {
		if (transformed.y < -radarsz) transformed.y = -radarsz;
		clamped = 1;
	}
	else {
		if (transformed.y > radarsz) transformed.y = radarsz;
		clamped = 1;
	}

	if (e->IsDormant())
		i::surface->DrawSetColor(colors::gray);
	else
		i::surface->DrawSetColor(clr);

	i::surface->DrawFilledRect(transformed.x + center.x -2, -transformed.y + center.y -2, transformed.x + center.x + 2, -transformed.y + center.y + 2);
	i::surface->DrawSetColor(colors::black);
	i::surface->DrawOutlinedRect(transformed.x + center.x - 2, -transformed.y + center.y - 2, transformed.x + center.x + 2, -transformed.y + center.y + 2);
	//if (!clamped)
	//{
		i::surface->draw_string(fonts::Arial, transformed.x + center.x, -transformed.y + center.y, colors::white, text);
		//if (e->IsDormant()) i::surface->draw_string(fonts::Arial, transformed.x + center.x, -transformed.y + center.y + 15, colors::gray, "dormant");
	//}
}

void DrawRadarCarcass(int size,Vector pos)
{
	i::surface->DrawSetColor(colors::gray_t);
	i::surface->DrawFilledRect(pos.x - size / 2, pos.y - size / 2, pos.x + size / 2, pos.y + size / 2);
	i::surface->DrawSetColor(colors::white_t);
	i::surface->DrawLine(pos.x - size/2, pos.y, pos.x + size/2, pos.y);
	i::surface->DrawLine(pos.x, pos.y - size / 2, pos.x, pos.y + size / 2);
}

void Draw3DBox(CBaseEntity* ent)
{
	i::surface->DrawSetColor(colors::orange);

	ESPBox b;

	if (GetBox(ent, b))
	{
		i::surface->DrawLine(b.blt.x, b.blt.y, b.brt.x, b.brt.y);
		i::surface->DrawLine(b.blt.x, b.blt.y, b.flt.x, b.flt.y);
		i::surface->DrawLine(b.blt.x, b.blt.y, b.blb.x, b.blb.y);

		i::surface->DrawLine(b.frt.x, b.frt.y, b.brt.x, b.brt.y);
		i::surface->DrawLine(b.frt.x, b.frt.y, b.frb.x, b.frb.y);
		i::surface->DrawLine(b.frt.x, b.frt.y, b.flt.x, b.flt.y);

		i::surface->DrawLine(b.flb.x, b.flb.y, b.flt.x, b.flt.y);
		i::surface->DrawLine(b.flb.x, b.flb.y, b.blb.x, b.blb.y);
		i::surface->DrawLine(b.flb.x, b.flb.y, b.frb.x, b.frb.y);

		i::surface->DrawLine(b.flb.x, b.flb.y, b.flt.x, b.flt.y);
		i::surface->DrawLine(b.flb.x, b.flb.y, b.blb.x, b.blb.y);
		i::surface->DrawLine(b.flb.x, b.flb.y, b.frb.x, b.frb.y);

		i::surface->DrawLine(b.brb.x, b.brb.y, b.brt.x, b.brt.y);
		i::surface->DrawLine(b.brb.x, b.brb.y, b.blb.x, b.blb.y);
		i::surface->DrawLine(b.brb.x, b.brb.y, b.frb.x, b.frb.y);
	}
}

void __stdcall PaintTraverse(unsigned int panel, bool forceRepaint, bool allowForce) noexcept
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		c::menu::state = !c::menu::state;
		if (!c::menu::state)
		{
			ImGui::GetIO().MouseDown[0] = false;
			i::inputSystem->resetInputState();
		}
	}


	v_panel->GetOriginal<void(__thiscall*)(void*, unsigned int, bool, bool)>(41)(i::panel, panel, forceRepaint, allowForce);

	static unsigned int drawpanel;
	if (!drawpanel)
	{
		const char* panelname = i::panel->GetName(panel);
		if (!strcmp(panelname, "OverlayPopupPanel"))
		{
			drawpanel = panel;
			fonts::Arial = i::surface->Create_Font();
			i::surface->SetFontGlyphSet(fonts::Arial, "Arial", 16, 600, 0, 0, FONTFLAG_OUTLINE);
		}
	}

	if (panel == drawpanel)
	{

		int w, h;
		i::surface->GetScreenSize(w, h);

		static float rainbow;
		rainbow += 0.00005f;
		if (rainbow > 1.f) rainbow = 0.f;

		i::panel->SetMouseInputEnabled(panel, c::menu::state);

		CBaseEntity* local = (CBaseEntity*)i::entitylist->GetClientEntity(i::engine->get_local_player());
		if (!local) return;
		if ((DWORD)local < 100) return;

		CBaseEntity* wep = (CBaseEntity*)i::entitylist->GetClientEntityFromHandle(local->GetActiveWeaponHandle());

		//i::surface->draw_string(fonts::Arial, 10, 10, colors::white, "%f", SpreadAngles);

		/*
		i::surface->draw_string(fonts::Arial, 10, 10, colors::white, "0x%x", local);
		if (wep)
		{
			i::surface->draw_string(fonts::Arial, 20, 25, colors::gray, "0x%x", wep);
			i::surface->draw_string(fonts::Arial, 20, 40, colors::gray, "name: %s", wep->GetWeaponName());
			i::surface->draw_string(fonts::Arial, 20, 55, colors::gray, "clip: %i/%i", wep->GetClipFirst(), wep->GetClipSecond());
			i::surface->draw_string(fonts::Arial, 20, 70, colors::gray, "state: %i", wep->GetWeaponState());
			i::surface->draw_string(fonts::Arial, 20, 85, colors::gray, "owner: 0x%x", i::entitylist->GetClientEntityFromHandle(wep->GetWeaponOwner()));
		}
		else {
			i::surface->draw_string(fonts::Arial, 20, 25, colors::gray, "null");
		}
		*/

		i::surface->DrawSetColor(colors::light_red);
		i::surface->DrawOutlinedCircle(w / 2, h / 2, c::aim::fov * 2, 180);


		DrawRadarCarcass(radarsz * 2, { 200,200,0 });


		for (size_t i = 1; i <= i::engine->get_max_clients(); i++)
		{
			CBaseEntity* entity = (CBaseEntity*)i::entitylist->GetClientEntity(i);
			if (!entity) continue;
			if (entity == nullptr) continue;
			if (!c::esp::allowdormant) if (entity->IsDormant()) continue;
			if (entity == local) continue;
			if (!entity->IsAlive()) continue;
			if (!c::esp::team && local->GetTeamNum() == entity->GetTeamNum()) continue;

			static player_info_t info;
			i::engine->get_player_info(i, &info);

			DrawOnRadar(local, entity, { 200,200,0 }, info.name, colors::green);

			static int v = 10;

			if (c::esp::esptoggled)
			{
				//aabb
				Vector s;
				if (WorldToScreen(entity->GetRenderOrigin(), s))
				{
					///*
					ESPBox b;

					static bool dormant;
					if (entity->IsDormant())
						dormant = true;
					else
						dormant = false;

					if (GetBox(entity, b))
					{
						//i::surface->DrawSetColor(dormant ? colors::gray : FromHSB(rainbow, 1.f, 1.f));
						i::surface->DrawSetColor(dormant ? colors::gray : colors::green);
						i::surface->DrawLine(b.blt.x, b.blt.y, b.brt.x, b.brt.y);
						i::surface->DrawLine(b.blt.x, b.blt.y, b.flt.x, b.flt.y);
						i::surface->DrawLine(b.blt.x, b.blt.y, b.blb.x, b.blb.y);

						i::surface->DrawLine(b.frt.x, b.frt.y, b.brt.x, b.brt.y);
						i::surface->DrawLine(b.frt.x, b.frt.y, b.frb.x, b.frb.y);
						i::surface->DrawLine(b.frt.x, b.frt.y, b.flt.x, b.flt.y);

						i::surface->DrawLine(b.flb.x, b.flb.y, b.flt.x, b.flt.y);
						i::surface->DrawLine(b.flb.x, b.flb.y, b.blb.x, b.blb.y);
						i::surface->DrawLine(b.flb.x, b.flb.y, b.frb.x, b.frb.y);

						i::surface->DrawLine(b.flb.x, b.flb.y, b.flt.x, b.flt.y);
						i::surface->DrawLine(b.flb.x, b.flb.y, b.blb.x, b.blb.y);
						i::surface->DrawLine(b.flb.x, b.flb.y, b.frb.x, b.frb.y);

						i::surface->DrawLine(b.brb.x, b.brb.y, b.brt.x, b.brt.y);
						i::surface->DrawLine(b.brb.x, b.brb.y, b.blb.x, b.blb.y);
						i::surface->DrawLine(b.brb.x, b.brb.y, b.frb.x, b.frb.y);
					}
					//*/
					player_info_t info;
					i::engine->get_player_info(i, &info);
					i::surface->draw_string(fonts::Arial, s.x, s.y - 40, dormant ? colors::gray : colors::white, info.name);
					i::surface->draw_string(fonts::Arial, s.x, s.y - 25, dormant ? colors::gray : colors::green, "%i", entity->GetHealth());
					//i::surface->draw_string(fonts::Arial, s.y, s.y + 10, entity->getteamcolor(), "team");


					static int count;

					harray weapons = entity->GetAllWeapons();
					for (size_t i = 0; i < 16; i++)
					{
						if (!weapons.a[i]) continue;
						CBaseEntity* weapon = (CBaseEntity*)(i::entitylist->GetClientEntityFromHandle(weapons.a[i]));
						if (!weapon) continue;

						bool active = false;
						if (weapons.a[i] == entity->GetActiveWeaponHandle()) active = true;

						const char* name = weapon->GetWeaponNameInternal();
						//if (name = "") name = "Unknown";

						i::surface->draw_string(fonts::Arial, s.x, s.y + count * 15, active ? colors::white : colors::gray, "%s", name);
						count++;
					}
					count = 0;

				}

				//headdot
				if (!entity->IsDormant())
				{
					if (WorldToScreen(entity->GetHitboxPosition(0, i::modelinfo, i::globals->GetGlobalVars()->curtime), s))
					{
						i::surface->DrawSetColor(colors::red);
						i::surface->DrawOutlinedCircle(s.x, s.y, 2, 180);
					}
				}
			}
		}


		for (size_t i = i::engine->get_max_clients(); i <= i::entitylist->GetHighestEntityIndex(); i++)
		{
			CBaseEntity* entity = (CBaseEntity*)i::entitylist->GetClientEntity(i);
			if (!entity) continue;

			if (entity->GetOrigin().IsZero()) continue;
			if (entity->IsWeapon() && entity->GetWeaponOwner() > 0) continue;

			Vector s, f;
			if (WorldToScreen(entity->GetRenderOrigin(), s))
			{
				if (c::esp::bot)
				{
					if (entity->GetClientClass()->iClassID == classids::CAI_BaseNPC)
					{
						DrawOnRadar(local, entity, { 200,200,0 }, "npc", colors::orange);
						Draw3DBox(entity);
						if (WorldToScreen(entity->GetHitboxPosition(0, i::modelinfo, i::globals->GetGlobalVars()->curtime), f))
						{
							i::surface->DrawSetColor(colors::red);
							i::surface->DrawOutlinedCircle(f.x, f.y, 4, 180);
						}

						auto hdr = i::modelinfo->GetStudiomodel(entity->GetModel());
						if (hdr)
						{
							i::surface->DrawSetColor(colors::white);
							Vector v_parent, v_child, s_parent, s_child;

							for (int i = 0; i < hdr->numbones; i++) {
								mstudiobone_t* bone = hdr->GetBone(i);

								if (bone)
								{
									if (bone && (bone->flags & 0x00000100) && (bone->parent != -1)) {
										v_child = entity->get_bone_pos(i, i::globals->GetGlobalVars()->curtime);
										v_parent = entity->get_bone_pos(bone->parent, i::globals->GetGlobalVars()->curtime);

										if (WorldToScreen(v_parent, s_parent) && WorldToScreen(v_child, s_child))
										{
											i::surface->DrawLine(s_parent.x, s_parent.y, s_child.x, s_child.y);
										}
									}
								}
							}
						}
					}
				}

				if (c::esp::debugesp)
				{
					switch (entity->GetClientClass()->iClassID)
					{
					case classids::CSENT_anim:
						if (!strcmp(entity->GetWeaponName(), "Spawned Weapon"))
						{
							i::surface->draw_string(fonts::Arial, s.x, s.y, colors::orange, "%s", entity->GetScriptName().n);
							if (c::radar::pickups) DrawOnRadar(local, entity, { 200,200,0 }, entity->GetScriptName().n, colors::orange);
							Draw3DBox(entity);
						}
						else if (strcmp(entity->GetWeaponName(), "")) {
							i::surface->draw_string(fonts::Arial, s.x, s.y, colors::orange, "%s", entity->GetWeaponName());
							if (c::radar::pickups) DrawOnRadar(local, entity, { 200,200,0 }, entity->GetWeaponName(), colors::orange);
							Draw3DBox(entity);
						}
						break;
					case classids::CWeaponSWEP:
						i::surface->draw_string(fonts::Arial, s.x, s.y, colors::orange, "%s", entity->GetWeaponName());
						if (c::radar::pickups) DrawOnRadar(local, entity, { 200,200,0 }, entity->GetWeaponName(), colors::orange);
						Draw3DBox(entity);
						break;
					default:
						break;
					}
				}

				//i::surface->draw_string(fonts::Arial, s.x, s.y, colors::orange, "%s", entity->GetWeaponName());
				//i::surface->draw_string(fonts::Arial, s.x, s.y + 15, colors::orange, "id: %i", entity->GetClientClass()->iClassID);
				//i::surface->draw_string(fonts::Arial, s.x, s.y + 30, colors::orange, "%s", entity->GetScriptName().n);
				//i::surface->draw_string(fonts::Arial, s.x, s.y + 45, colors::orange, "0x%x",entity);
			}
		}


		if (c::misc::crosshair && c::misc::crosshairsize > 0)
		{
			static int h, w;
			i::engine->get_screen_size(h, w);

			i::surface->DrawSetColor(colors::red);
			i::surface->DrawLine(h / 2 - c::misc::crosshairsize, w / 2, h / 2 + c::misc::crosshairsize, w / 2);
			i::surface->DrawLine(h / 2, w / 2 - c::misc::crosshairsize, h / 2, w / 2 + c::misc::crosshairsize);
		}
	}
}

void DoSpreadFAS(CUserCmd* cmd)
{
	CBaseEntity* localplayer = (CBaseEntity*)(i::entitylist->GetClientEntity(i::engine->get_local_player()));
	CBaseEntity* wep = (CBaseEntity*)(i::entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeaponHandle()));

	if (!localplayer && !wep) return;

	if (!(cmd->buttons & IN_ATTACK))
		return;

	float cone = wep->get_fas2_cone();

	if (cone == 0.f)
		return;

	wep->RandomSeed(localplayer->m_nTickBase() * i::globals->GetGlobalVars()->interval_per_tick);

	float x = wep->Rand(-cone, cone);
	float y = wep->Rand(-cone, cone);

	Vector nospread = cmd->viewangles + Vector(-x, -y, 0) * 25;
	cmd->viewangles = nospread;
}

bool lasttick = false;
int oldtick = 0;
Vector oldang = { 0,0,0 };

bool __stdcall CreateMove(float input_sample_frametime, CUserCmd* cmd) noexcept
{
	if (!cmd->command_number)
		return false;

	CBaseEntity* local = (CBaseEntity*)(i::entitylist->GetClientEntity(i::engine->get_local_player()));

	if (!local)
		return false;

	CBaseEntity* wep = (CBaseEntity*)(i::entitylist->GetClientEntityFromHandle(local->GetActiveWeaponHandle()));

	if (!wep)
		return false;

	if ((DWORD)local < 100) return false;

	//auto base = reinterpret_cast<uintptr_t>(_AddressOfReturnAddress()) - sizeof(uintptr_t);
	//bool& bSendPacket = *(***reinterpret_cast<bool****>(base) - 1);

	int w, h;
	i::surface->GetScreenSize(w, h);

	//SpreadAngles = SpreadAngle(cmd, wep);

	//SpreadAngles = wep->get_fas2_cone();

	//if (cmd->buttons & IN_ATTACK && wep->CanShoot())
	//{
		//cmd->viewangles += SpreadAngles;
	//}

	//DoSpreadFAS(cmd);

	if (c::aim::botstate)
	{
		if (cmd->buttons & IN_ATTACK)
		{
			CBaseEntity* target = 0;
			float lowestDist = 10000;
			Vector w2sHead;
			for (int i = i::engine->get_max_clients(); i <= i::entitylist->GetHighestEntityIndex(); i++)
			{
				CBaseEntity* entity = (CBaseEntity*)(i::entitylist->GetClientEntity(i));
				if (!entity) continue;
				if (entity->GetClientClass()->iClassID != classids::CAI_BaseNPC) continue;
				if (!entity->IsAlive()) continue;
				if (entity == local) continue;
				if (entity->IsDormant()) continue;
				if (!c::aim::team && local->GetTeamNum() == entity->GetTeamNum()) continue;

				Vector angles;
				Vector our_pos = local->GetOrigin() + local->GetViewOffset();
				Vector enemypos = entity->GetHitboxPosition(0, i::modelinfo, i::globals->GetGlobalVars()->curtime);
				enemypos -= our_pos;
				VectorAngles(enemypos, angles);

				Vector pos = entity->GetHitboxPosition(0, i::modelinfo, i::globals->GetGlobalVars()->curtime);
				if (pos.x != 0 && pos.y != 0 && pos.z != 0)
				{
					WorldToScreen(pos, w2sHead);

					double dist = sqrt(pow((w / 2) - w2sHead.x, 2) + pow((h / 2) - w2sHead.y, 2));

					if (dist < lowestDist)
					{
						lowestDist = dist;
						target = entity;
					}
				}
			}

			if (target)
			{
				Vector pos = target->GetHitboxPosition(0, i::modelinfo, i::globals->GetGlobalVars()->curtime);
				if (pos.x != 0 && pos.y != 0 && pos.z != 0)
				{
					WorldToScreen(pos, w2sHead);

					float headX = (w2sHead.x - (w / 2)) / 2;
					float headY = (w2sHead.y - (h / 2)) / 2;

					if (headX > -c::aim::fov && headX < c::aim::fov && headY < c::aim::fov && headY > -c::aim::fov) {
						oldang = cmd->viewangles;
						Vector our_pos = local->GetOrigin() + local->GetViewOffset();
						pos -= our_pos;
						VectorAngles(pos, cmd->viewangles);
					}
				}
			}
		}
	}

	if (c::aim::state)
	{
		if (cmd->buttons & IN_ATTACK)
		{
			CBaseEntity* target = 0;
			float lowestDist = 10000;
			Vector w2sHead;
			for (int i = 0; i <= i::engine->get_max_clients(); i++)
			{
				CBaseEntity* entity = (CBaseEntity*)(i::entitylist->GetClientEntity(i));
				if (!entity) continue;
				if (!entity->IsAlive()) continue;
				if (entity == local) continue;
				if (entity->IsDormant()) continue;
				if (!c::aim::team && local->GetTeamNum() == entity->GetTeamNum()) continue;

				Vector angles;
				Vector our_pos = local->GetOrigin() + Vector{ 0,0,64 };
				Vector enemypos = entity->GetHitboxPosition(0, i::modelinfo, i::globals->GetGlobalVars()->curtime);
				enemypos -= our_pos;
				VectorAngles(enemypos, angles);

				Vector pos = entity->GetHitboxPosition(0, i::modelinfo, i::globals->GetGlobalVars()->curtime);
				if (pos.x != 0 && pos.y != 0 && pos.z != 0)
				{
					WorldToScreen(pos, w2sHead);

					double dist = sqrt(pow((w / 2) - w2sHead.x, 2) + pow((h / 2) - w2sHead.y, 2));

					if (dist < lowestDist)
					{
						lowestDist = dist;
						target = entity;
					}
				}
			}

			if (target)
			{
				Vector pos = target->GetHitboxPosition(0, i::modelinfo, i::globals->GetGlobalVars()->curtime);
				if (pos.x != 0 && pos.y != 0 && pos.z != 0)
				{
					WorldToScreen(pos, w2sHead);

					float headX = (w2sHead.x - (w / 2)) / 2;
					float headY = (w2sHead.y - (h / 2)) / 2;

					if (headX > -c::aim::fov && headX < c::aim::fov && headY < c::aim::fov && headY > -c::aim::fov) {
						oldang = cmd->viewangles;
						Vector our_pos = local->GetOrigin() + Vector{ 0,0,64 };
						pos -= our_pos;
						VectorAngles(pos, cmd->viewangles);
					}
				}
			}
		}
	}

	if (c::misc::bhop)
	{
		if (cmd->buttons & IN_JUMP && !(local->GetFlags() & FL_ONGROUND))
		{
			cmd->buttons &= ~IN_JUMP;
		}
	}

	if (!oldang.IsZero())
	{
		lasttick = true;
		oldtick = cmd->tick_count;
	}


	if (lasttick && oldtick)
	{
		if (oldtick != cmd->tick_count)
		{
			cmd->viewangles = oldang;
			oldang = { 0,0,0 };
			lasttick = false;
			oldtick = 0;
		}
	}

	v_clientmode->GetOriginal<bool(__thiscall*)(IClientModeShared*, float, CUserCmd*)>(21)(i::clientmode, input_sample_frametime, cmd);

	return false;
}

float __stdcall GetViewModelFov() noexcept
{
	return v_clientmode->GetOriginal<float(__thiscall*)(IClientModeShared*)>(32)(i::clientmode) + c::misc::viewmodelfov;
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static LRESULT __stdcall wndProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (c::menu::state)
	{
		ImGui_ImplWin32_WndProcHandler(window, msg, wParam, lParam);
		return true;
	}

	return CallWindowProc(dx::originalWndProc, window, msg, wParam, lParam);
}

void colorPicker(const char* name, ImVec4 color, float *colorz) noexcept
{
	ImGui::PushID(name);
	bool openPopup = ImGui::ColorButton("##btn", color, ImGuiColorEditFlags_NoTooltip);
	ImGui::SameLine(0.0f, 5.0f);
	ImGui::TextUnformatted(name);

	if (openPopup)
		ImGui::OpenPopup("##popup");

	if (ImGui::BeginPopup("##popup")) {
		ImGui::ColorPicker3("##picker", colorz, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_NoSidePreview);

		ImGui::EndPopup();
	}
	ImGui::PopID();
}

int currentcat = 0;
int yet = 0;

static HRESULT __stdcall present(IDirect3DDevice9* device, const RECT* src, const RECT* dest, HWND windowOverride, const RGNDATA* dirtyRegion) noexcept
{
	static bool imguiInit{ ImGui_ImplDX9_Init(device) };

	if (c::menu::state)
	{
		device->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE);
		IDirect3DVertexDeclaration9* vertexDeclaration;
		device->GetVertexDeclaration(&vertexDeclaration);

		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("cement", &c::menu::state,windowFlags);
		ImGui::SetWindowSize({ 400,400 });

		//ImGui::Button("uff yaa", ImVec2{ 100,20 });
		ImGui::Checkbox("##test", &c::test::b);
		ImGui::SameLine();
		ImGui::SliderFloat("viewfov", &c::misc::viewmodelfov, 0.f, 90.f,"%.0f");
		ImGui::SliderFloat("fov", &c::aim::fov, 0.f, 300.f, "%.0f");
		//colorPicker("team", ImVec4{ c::clr::team[0], c::clr::team[1], c::clr::team[2],255 }, c::clr::team);
		//colorPicker("enemy", ImVec4{ c::clr::enemy[0], c::clr::enemy[1], c::clr::enemy[2],255 }, c::clr::enemy);
		ImGui::Checkbox("debug esp", &c::esp::debugesp);
		//ImGui::Combo("", &currentcat, "All\0Pistols\0Heavy\0SMG\0Rifles\0");
		ImGui::Checkbox("##xhar", &c::misc::crosshair);
		ImGui::SameLine();
		ImGui::SliderInt("xhair", &c::misc::crosshairsize, 0, 300);
		ImGui::Checkbox("esp dormant", &c::esp::allowdormant);
		ImGui::Checkbox("esp toggle", &c::esp::esptoggled);
		ImGui::Checkbox("bhop", &c::misc::bhop);
		ImGui::Checkbox("aim", &c::aim::state);
		ImGui::Checkbox("team aim", &c::aim::team);
		ImGui::Checkbox("team esp", &c::esp::team);
		ImGui::SliderFloat("radar scale", &c::radar::zoom, 0.005, 1.f);
		ImGui::Checkbox("radar pickups", &c::radar::pickups);
		ImGui::Checkbox("bot aim", &c::aim::botstate);
		ImGui::Checkbox("bot esp", &c::esp::bot);
		//ImGui::Text("classes");
		//ImGui::BeginChild("Scrolling");
		//for (int n = 0; n <= i::entitylist->GetHighestEntityIndex(); ++n)
		//{
		//	CBaseEntity* entity = (CBaseEntity*)(i::entitylist->GetClientEntity(n));
		//	if (!entity) continue;
		//	ImGui::Text("%i. %s", n, entity->GetClientClass()->chName);
		//}
		//ImGui::EndChild();


		if (ImGui::ArrowButton("owo", yet))
		{
			yet++;
			if (yet == 4) yet = 0;
		}

		ImGui::BulletText("%i", yet);

		ImGui::End();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

		device->SetVertexDeclaration(vertexDeclaration);
		vertexDeclaration->Release();
	}

	return dx::oPresent(device, src, dest, windowOverride, dirtyRegion);
}

static HRESULT __stdcall reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	auto result = dx::oReset(device, params);
	ImGui_ImplDX9_CreateDeviceObjects();
	return result;
}


int startup(void* hModule)
{
	FILE* f;
	AllocConsole();
	freopen_s(&f, "CONOUT$", "w", stdout);

	ImGui::CreateContext();
	ImGui_ImplWin32_Init(FindWindowW(L"Valve001", NULL));

	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0;
	style.WindowTitleAlign = { 0.5f,0.5f };

	cock();

	printf("client - 0x%x\n", i::client);
	printf("entlist - 0x%x\n", i::entitylist);
	printf("panel - 0x%x\n", i::panel);
	printf("surface - 0x%x\n", i::surface);
	printf("clientmode - 0x%x\n", i::clientmode);

	dx::originalWndProc = WNDPROC(SetWindowLongPtrA(FindWindowW(L"Valve001", nullptr), GWLP_WNDPROC, LONG_PTR(wndProc)));

	dx::oPresent = **reinterpret_cast<decltype(dx::oPresent) * *>(dx::present);
	**reinterpret_cast<decltype(present)***>(dx::present) = present;
	dx::oReset = **reinterpret_cast<decltype(dx::oReset) * *>(dx::reset);
	**reinterpret_cast<decltype(reset)***>(dx::reset) = reset;

	//v_client = new VMTHook(i::client);
	//v_client->ApplyNewTable();

	v_panel = new VMTHook(i::panel);
	v_panel->SwapPointer(41, reinterpret_cast<void*>(PaintTraverse));
	v_panel->ApplyNewTable();

	v_clientmode = new VMTHook(i::clientmode);
	v_clientmode->SwapPointer(21, reinterpret_cast<void*>(CreateMove));
	v_clientmode->SwapPointer(32, reinterpret_cast<void*>(GetViewModelFov));
	v_clientmode->ApplyNewTable();

	DumpClassIds();
	//i::netvar->Dump();


	//DWORD gpGlobals = GetClientSignature((char*)"51 A1 ? ? ? ? 56 83 EC 08") + 2;

	//printf("0x%x\n", gpGlobals);

	//CGlobals* test = **(CGlobals***)gpGlobals;

	//printf("%f\n", test->curtime);
	//printf("%i\n", test->tickcount);
	//printf("%f\n", test->interpolation_amount);

	for (; !(GetAsyncKeyState(VK_HOME) & 1); std::this_thread::sleep_for(std::chrono::milliseconds(25)));

	SetWindowLongPtrA(FindWindowW(L"Valve001", nullptr), GWLP_WNDPROC, LONG_PTR(dx::originalWndProc));
	**reinterpret_cast<void***>(dx::present) = dx::oPresent;
	**reinterpret_cast<void***>(dx::reset) = dx::oReset;

	//v_client->RestoreOldTable();
	v_clientmode->RestoreOldTable();
	v_panel->RestoreOldTable();

	//free resources
	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread((HMODULE)hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		//i want to die
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)startup, hModule, 0, nullptr);
		break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

