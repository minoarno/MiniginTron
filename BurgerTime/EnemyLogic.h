#pragma once
#include "BaseComponent.h"

class EnemyLogic final : public BaseComponent
{
public:
	EnemyLogic(float speed, int score);
	EnemyLogic(const EnemyLogic&) = delete;
	EnemyLogic& operator=(const EnemyLogic&) = delete;
	EnemyLogic(EnemyLogic&&) = delete;
	EnemyLogic& operator=(EnemyLogic&&) = delete;
	~EnemyLogic() = default;

protected:
	void Initialize() override;

private:
	int m_Score{};
	float m_Speed{};
};