#include "MiniginPCH.h"
#include "RigidBody.h"
#include "GameObject.h"

#include "Scene.h"
#include "Box2D.h"

RigidBody::RigidBody(bool isStatic)
	: BaseComponent{}
{
	m_BodyDef.type = (isStatic) ? b2_staticBody : b2_dynamicBody;
}

RigidBody::~RigidBody()
{
	b2World* pWorld = m_pGameObject->GetScene()->GetWorld();
	if (pWorld != nullptr)
	{
		if (pWorld->IsLocked())
		{
			ME_CORE_ERROR("Removal while physics step is active");
		}
		pWorld->DestroyBody(m_pBody);
	}
}

b2Fixture* RigidBody::AddCollider(const b2FixtureDef& fixtureDef)
{
	return m_pBody->CreateFixture(&fixtureDef);
}

void RigidBody::Move(const float x, const float y)
{
	auto linearVelocity = m_pBody->GetLinearVelocity();
	linearVelocity.x += x;
	linearVelocity.y += y;
	m_pBody->SetLinearVelocity(linearVelocity);
}

void RigidBody::Initialize()
{
	m_BodyDef.userData = m_pGameObject;

	auto pos = m_pGameObject->GetComponent<dae::Transform>()->GetWorldPosition();
	m_BodyDef.position = {pos.x, pos.y};
	m_BodyDef.fixedRotation = true;

	m_pBody = m_pGameObject->GetScene()->GetWorld()->CreateBody(&m_BodyDef);
}

void RigidBody::Update()
{
	if (m_pBody == nullptr) return;

	auto pos = m_pBody->GetPosition();
	m_pGameObject->GetComponent<dae::Transform>()->SetLocalPosition(pos.x, pos.y, 0);
}
