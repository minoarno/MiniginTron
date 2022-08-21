#pragma once

struct Rect
{
	float x;
	float y;
	float w;
	float h;
};

struct Color
{
	float r;
	float g;
	float b;
};

struct Vector2
{
	float x;
	float y;


	Vector2()
		:x{0}
		,y{0}
	{
	}
	Vector2(float x, float y)
		: x{x}
		, y{y}
	{
	}
	Vector2(int x, int y)
		: x{ float(x) }
		, y{ float(y) }
	{
	}
};