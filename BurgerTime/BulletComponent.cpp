#include "TronPCH.h"
#include "BulletComponent.h"
#include "GameObject.h"
#include "Player.h"
#include "Lives.h"
#include "Score.h"
#include "Scene.h"
#include "EnemyLogic.h"
#include "Timer.h"
#include "TimerCallback.h"
#include "RigidBody.h"

BulletComponent::BulletComponent(Player* pPlayer)
	: m_pPlayer{ pPlayer }
{
}

void BulletComponent::Initialize()
{
	m_pGameObject->AddCollisionCallback([=](b2Fixture*, b2Fixture* pOtherFixture, b2Contact*, CollisionType contactType)
		{
			if (!m_pGameObject->GetActive())return;
			if (contactType != CollisionType::BeginContact) return;

			dae::GameObject* other = static_cast<dae::GameObject*>(pOtherFixture->GetUserData());
			if (!other->GetActive())return;

			if (other->GetTag() == "Enemy" && m_pGameObject->GetTag() == "PlayerBullet")
			{
				m_pGameObject->SetActive(false);
				m_pGameObject->GetScene()->RemoveObject(m_pGameObject);

				if (m_pPlayer != nullptr)
				{
					m_pPlayer->GetScore()->IncreaseScore(other->GetComponent<EnemyLogic>()->GetScore());
				}
				return;
			}

			if (other->GetTag() == "Player" && m_pGameObject->GetTag() == "EnemyBullet")
			{
				other->GetComponent<Player>()->GetLives()->LoseLife();
				m_pGameObject->SetActive(false);
				m_pGameObject->GetScene()->RemoveObject(m_pGameObject);
				return;
			}

			if (other->GetTag() == "Level")
			{
				m_CurrentAmountOfBounces++;
				auto vel = m_pGameObject->GetComponent<RigidBody>()->GetBody()->GetLinearVelocity();
				m_pGameObject->GetComponent<RigidBody>()->Move(vel.x * -1, vel.y * -1);
				if (m_CurrentAmountOfBounces >= m_MaxAmountOfBounces)
				{
					m_pGameObject->SetActive(false);
					m_pGameObject->GetScene()->RemoveObject(m_pGameObject);
				}
			}
		}
		
	);
}
