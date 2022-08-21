#include "TronPCH.h"
#include "EnemyLogic.h"

#include "GameObject.h"
#include "Scene.h"

#include "RigidBody.h"
#include <iostream>
EnemyLogic::EnemyLogic(float speed, int score, int hp)
	: m_Speed{ speed }
	, m_Score{ score }
	, m_Hitpoints{ hp }
{
}

void EnemyLogic::Initialize()
{
	m_pGameObject->AddCollisionCallback([=](b2Fixture* , b2Fixture* pOtherFixture, b2Contact* , CollisionType contactType)
		{
			if (!m_pGameObject->GetActive())return;

			dae::GameObject* other = static_cast<dae::GameObject*>(pOtherFixture->GetUserData());
			if (contactType != CollisionType::BeginContact) return;
			
			if (other->GetTag() == "PlayerBullet")
			{
				m_Hitpoints--;
				if (m_Hitpoints <= 0)
				{
					m_pGameObject->SetActive(false);
					m_pGameObject->GetScene()->RemoveObject(m_pGameObject);
				}
			}
		}
	);
}

void EnemyLogic::Update()
{

	m_pGameObject->GetComponent<RigidBody>()->Move(0,0);
}
