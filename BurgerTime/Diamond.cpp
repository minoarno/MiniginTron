#include "TronPCH.h"
#include "Diamond.h"

#include "GameObject.h"

Diamond::Diamond(const std::function<void()>& func)
	: BaseComponent{}
	, m_Func{ func }
{
}

void Diamond::Initialize()
{
	m_pGameObject->AddCollisionCallback([=](b2Fixture*, b2Fixture* pOtherFixture, b2Contact*, CollisionType contactType)
		{
			if (!m_pGameObject->GetActive())return;
			if (contactType != CollisionType::BeginContact) return;

			dae::GameObject* other = static_cast<dae::GameObject*>(pOtherFixture->GetUserData());
			if (!other->GetActive())return;

			if (other->GetTag() == "Player")
			{
				m_Func();
			}
		});
}
