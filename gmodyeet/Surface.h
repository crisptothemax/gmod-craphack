#pragma once
#include "method.h"
#include <algorithm>

namespace fonts
{
	DWORD Arial = 0;
}

struct Color
{
	int r, g, b, a = 255;
};

static Color FromHSB(float hue, float saturation, float brightness)
{
	float h = hue == 1.0f ? 0 : hue * 6.0f;
	float f = h - (int)h;
	float p = brightness * (1.0f - saturation);
	float q = brightness * (1.0f - saturation * f);
	float t = brightness * (1.0f - (saturation * (1.0f - f)));

	if (h < 1)
	{
		return Color{
			(int)(brightness * 255),
			(int)(t * 255),
			(int)(p * 255)
		};
	}
	else if (h < 2)
	{
		return Color{
			(int)(q * 255),
			(int)(brightness * 255),
			(int)(p * 255)
		};
	}
	else if (h < 3)
	{
		return Color{
			(int)(p * 255),
			(int)(brightness * 255),
			(int)(t * 255)
		};
	}
	else if (h < 4)
	{
		return Color{
			(int)(p * 255),
			(int)(q * 255),
			(int)(brightness * 255)
		};
	}
	else if (h < 5)
	{
		return Color{
			(int)(t * 255),
			(int)(p * 255),
			(int)(brightness * 255)
		};
	}
	else
	{
		return Color{
			(int)(brightness * 255),
			(int)(p * 255),
			(int)(q * 255)
		};
	}
}

namespace colors
{
	Color orange{ 255, 170, 0,255 };
	Color red{ 255,0,0,255 };
	Color green{ 0,255,0,255 };
	Color black{ 0,0,0,255 };
	Color white{ 255,255,255,255 };
	Color white_t{ 255,255,255,100 };
	Color blue{ 43, 0, 255,255 };
	Color lightgreen{ 174, 227, 0 ,255 };
	Color gray_t{ 145, 145, 145 ,120 };
	Color light_red{ 255,0,0,100 };
	Color light_black{ 13, 13, 13,255 };
	Color greenshit{ 180, 240, 50,255 };
	Color gray{ 150,150,150,255 };

	Color pickuphp{ 120, 245, 66 ,255 };
	Color pickupammo{ 245, 150, 66 ,255 };
}

enum FontDrawType_t
{
	// Use the "additive" value from the scheme file
	FONT_DRAW_DEFAULT = 0,

	// Overrides
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,

	FONT_DRAW_TYPE_COUNT = 2,
};

enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

class ISurface
{
public:
	void UnlockCursor()
	{
		using UnlockCursor = void(__thiscall*)(void*);
		return method<UnlockCursor>(61, this)(this);
	}

	void SetCursorAllwaysVisible(bool state)
	{
		using SetCursorAllwaysVisible = void(__thiscall*)(void*, bool);
		return method<SetCursorAllwaysVisible>(52, this)(this, state);
	}

	inline void GetCursorPos(int& x, int& y) noexcept
	{
		using GetCursorPos = void(__thiscall*)(void*, int&, int&);
		return method<GetCursorPos>(96, this)(this, x, y);
	}

	inline void DrawFilledRectFastFade(int x0, int y0, int x1, int y1, int fadeStartPt, int fadeEndPt, unsigned int alpha0, unsigned int alpha1, bool bHorizontal) noexcept
	{
		using DrawFilledRectFastFade = void(__thiscall*)(void*, int, int, int, int, int, int, unsigned int, unsigned int, bool);
		return method<DrawFilledRectFastFade>(117, this)(this, x0, y0, x1, y1, fadeStartPt, fadeEndPt, alpha0, alpha1, bHorizontal);
	}

	inline void DrawSetColor(Color color) noexcept
	{
		using DrawSetColor = void(__thiscall*)(void*, Color);
		return method<DrawSetColor>(11, this)(this, color);
	}

	inline void DrawFilledRect(int x, int y, int x1, int y1) noexcept
	{
		using DrawFilledRect = void(__thiscall*)(void*, int, int, int, int);
		return method<DrawFilledRect>(12, this)(this, x, y, x1, y1);
	}

	inline void DrawOutlinedRect(int x, int y, int x1, int y1) noexcept
	{
		using DrawOutlinedRect = void(__thiscall*)(void*, int, int, int, int);
		return method<DrawOutlinedRect>(14, this)(this, x, y, x1, y1);
	}

	inline void DrawLine(int x, int y, int x1, int y1) noexcept
	{
		using DrawLine = void(__thiscall*)(void*, int, int, int, int);
		return method<DrawLine>(15, this)(this, x, y, x1, y1);
	}

	inline int GetScreenSize(int& x, int& y) noexcept
	{
		using GetScreenSize = int(__thiscall*)(void*, int&, int&);
		return method<GetScreenSize>(38, this)(this, x, y);
	}

	unsigned long Create_Font() noexcept
	{
		using Create_Font = unsigned long(__thiscall*)(void*);
		return method<Create_Font>(66, this)(this);
	}

	void SetFontGlyphSet(unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags) noexcept
	{
		using SetFontGlyphSet = void(__thiscall*)(void*, unsigned long, const char*, int, int, int, int, int, int, int);
		return method<SetFontGlyphSet>(67, this)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}

	void DrawSetTextFont(unsigned long font) noexcept
	{
		using DrawSetTextFont = void(__thiscall*)(void*, unsigned long);
		return method<DrawSetTextFont>(17, this)(this, font);
	}

	void DrawOutlinedCircle(int x, int y, int r, int segments) noexcept
	{
		using DrawOutlinedCircle = void(__thiscall*)(void*, int, int, int, int);
		return method<DrawOutlinedCircle>(100, this)(this, x, y, r, segments);
	}

	void DrawColoredCircle(int x, int y, float radius, int r, int g, int b, int a) noexcept
	{
		using DrawColCircle = void(__thiscall*)(void*, int, int, float, int, int, int, int);
		return method<DrawColCircle>(166, this)(this, x, y, radius, r, g, b, a);
	}

	void GetTextSize(unsigned long font, const wchar_t* text, int& width, int& height)
	{
		using GetTextSize = void(__thiscall*)(void*, unsigned long, const wchar_t*, int&, int&);
		return method<GetTextSize>(75, this)(this, font, text, width, height);
	}

	void DrawSetTextColor(Color color) noexcept
	{
		using DrawSetTextColor = void(__thiscall*)(void*, Color);
		return method<DrawSetTextColor>(19, this)(this, color);
	}

	void DrawSetTextPos(int x, int y) noexcept
	{
		using DrawSetTextPos = void(__thiscall*)(void*, int, int);
		return method<DrawSetTextPos>(20, this)(this, x, y);
	}

	void DrawPrintText(wchar_t const* text, int len) noexcept
	{
		using DrawPrintText = void(__thiscall*)(void*, wchar_t const*, int, int);
		return method<DrawPrintText>(22, this)(this, text, len, 0);
	}

	void draw_string(DWORD font, int x, int y, Color col, const char* pszText, ...) noexcept
	{
		if (pszText == NULL)
			return;

		va_list va_alist;
		char szBuffer[1024] = { '\0' };
		wchar_t szString[1024] = { '\0' };

		va_start(va_alist, pszText);
		vsprintf_s(szBuffer, pszText, va_alist);
		va_end(va_alist);

		wsprintfW(szString, L"%S", szBuffer);
		DrawSetTextPos(x, y);
		DrawSetTextFont(font);
		DrawSetTextColor(col);
		DrawPrintText(szString, wcslen(szString));
	}
};