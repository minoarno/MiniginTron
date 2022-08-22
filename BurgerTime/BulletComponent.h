#pragma once
#include "BaseComponent.h"

class Player;
class BulletComponent final: public BaseComponent
{
public:
	BulletComponent() = default;
	BulletComponent(Player* pPlayer);
	BulletComponent(const BulletComponent&) = delete;
	BulletComponent& operator=(const BulletComponent&) = delete;
	BulletComponent(BulletComponent&&) = delete;
	BulletComponent& operator=(BulletComponent&&) = delete;
	~BulletComponent() = default;

protected:
	void Initialize() override;


private:
	int m_MaxAmountOfBounces{ 5 };
	int m_CurrentAmountOfBounces{ 0 };

	Player* m_pPlayer{ nullptr };
};
