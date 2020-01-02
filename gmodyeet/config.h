#pragma once

namespace c
{
	namespace menu
	{
		bool state = false;
	}

	namespace test
	{
		int i = 0;
		float f = 0;
		bool b = 0;
	}

	namespace aim
	{
		bool state = false;
		float fov = 70;
		bool team = false;
		bool botstate = false;
	}



	namespace esp
	{
		bool debugesp = false;
		bool allowdormant = false;
		bool team = false;
		bool esptoggled = false;
		bool bot = false;
	}

	namespace radar
	{
		float zoom = 0.01f;
		bool pickups = false;
	}

	namespace misc
	{
		float viewmodelfov = 0;
		bool crosshair = false;
		int crosshairsize = 0;
		bool bhop = false;

	}

	namespace clr
	{
		float team[3];
		float enemy[3];
	}
}