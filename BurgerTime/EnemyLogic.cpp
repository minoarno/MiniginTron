#include "TronPCH.h"
#include "EnemyLogic.h"

#include "GameObject.h"
#include "Scene.h"

#include "RigidBody.h"
#include <iostream>

#include "HelperStructs.h"
#include "EngineTime.h"
#include "Timer.h"
#include "TimerCallback.h"
#include "Player.h"
#include "TronCommands.h"

EnemyLogic::EnemyLogic(float speed, int score, int hp, const std::vector<Player*>& players)
	: m_Speed{ speed }
	, m_Score{ score }
	, m_Hitpoints{ hp }
{
	m_pPlayers = players;
}

EnemyLogic::~EnemyLogic()
{
	delete m_pTimerCallBack;
	m_pTimerCallBack = nullptr;
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

	m_pTimer = m_pGameObject->AddComponent(new Timer{ 1.3f,true });
	m_pTimerCallBack = m_pTimer->AddObserver(new TimerCallback{ [=]()
		{
				auto pWorld = m_pGameObject->GetScene()->GetWorld();
				auto pos = m_pGameObject->GetComponent<dae::Transform>()->GetWorldPosition();

				RaycastCallback hitInfo{ 0 };
				for (size_t i = 0; i < m_pPlayers.size(); i++)
				{
					auto posPlayer = m_pPlayers[i]->GetGameObject()->GetComponent<dae::Transform>()->GetWorldPosition();
					Vector2 direction = { posPlayer.x - pos.x, posPlayer.y - pos.y };
					pWorld->RayCast(&hitInfo, { pos.x,pos.y }, { pos.x + direction.x * 60,pos.y + direction.y * 60 });
				
					if (!hitInfo.hasHit())
					{
						Vector2 position{ pos.x + direction.x * m_Speed, pos.y + direction.y * m_Speed };

						//m_pGameObject->GetScene()->AddObject(Prefab::CreateBullet(position, direction, m_pGameObject->GetScene(), "EnemyBullet"));
					}
				}


				std::vector<Vector2> directions{};

				const float lengthRay{ 20.f };
				pWorld->RayCast(&hitInfo, { pos.x,pos.y }, { pos.x,pos.y + lengthRay });
				if (!hitInfo.hasHit())
				{
					directions.emplace_back(Vector2{ pos.x,pos.y + lengthRay });
				}

				pWorld->RayCast(&hitInfo, { pos.x,pos.y }, { pos.x,pos.y - lengthRay });
				if (!hitInfo.hasHit())
				{
					directions.emplace_back(Vector2{ pos.x,pos.y - lengthRay });
				}

				pWorld->RayCast(&hitInfo, { pos.x,pos.y }, { pos.x + lengthRay,pos.y });
				if (!hitInfo.hasHit())
				{
					directions.emplace_back(Vector2{ pos.x + lengthRay,pos.y });
				}

				pWorld->RayCast(&hitInfo, { pos.x,pos.y }, { pos.x - lengthRay,pos.y });
				if (!hitInfo.hasHit())
				{
					directions.emplace_back(Vector2{ pos.x - lengthRay,pos.y });
				}

				Vector2 target = directions[std::rand() % directions.size()];
				m_Direction = { target.x - pos.x, target.y - pos.y };
				m_EnemyState = EnemyState::wander;
		} });
}

void EnemyLogic::Update()
{
	auto pos = m_pGameObject->GetComponent<dae::Transform>()->GetWorldPosition();

	switch (m_EnemyState)
	{
	case EnemyState::searching:
	default:


		break;
	case EnemyState::wander:
		{
			
			float elapsed = float(Time::GetInstance().GetElapsedSeconds());
			m_pGameObject->GetComponent<RigidBody>()->Move(m_Direction.x * elapsed, m_Direction.y * elapsed);
		}
		break;
	case EnemyState::shooting:

		break;
	}

	if (m_EnemyState == EnemyState::wander)
	{

	}
}
