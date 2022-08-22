#include "MiniginPCH.h"
#include "HelperStructs.h"

float32 RaycastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32)
{
	hit = (fixture->GetFilterData().categoryBits & m_Category) == fixture->GetFilterData().categoryBits;
	if (hit)
	{
		m_CategoryHit = fixture->GetFilterData().categoryBits;
		fixHit = fixture;
		hitnormal = { normal.x, normal.y };
		hitpoint = { point.x, point.y };

	}
	else
	{
		return -1;
	}
	return 0;
}
