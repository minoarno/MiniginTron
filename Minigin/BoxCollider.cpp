#include "MiniginPCH.h"
#include "BoxCollider.h"
#include "Box2D.h"

BoxCollider::BoxCollider(const Vector2& dim, const Vector2& center)
	:ColliderComponent{}
{
	m_Shape = b2PolygonShape();
	m_Shape.SetAsBox(dim.x * .5f, dim.y * .5f, b2Vec2(float32(center.x), float32(center.y)), 0.f);
	m_Filter.maskBits = 0xFFFF;
	m_FixtureDef.density = 1.0f;
}

void BoxCollider::Initialize()
{
	ColliderComponent::Initialize();

	m_pFixture->SetSensor(false);
}
