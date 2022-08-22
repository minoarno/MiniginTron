#pragma once
#include "Box2D.h"

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

class RaycastCallback :public b2RayCastCallback
{
public:
	RaycastCallback(uint16 category) :m_Category(category) {}
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override;
	bool hasHit() { return hit; }
	b2Fixture* GetFixHit() { return fixHit; }
	Vector2 GetHitNormal() { return hitnormal; }
	Vector2 GetHitPoint() { return hitpoint; }
	uint16 m_CategoryHit = 0;
private:
	uint16 m_Category;

	Vector2 hitnormal;
	Vector2 hitpoint;

	bool hit = false;
	b2Fixture* fixHit = nullptr;
};