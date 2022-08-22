#pragma once
#include "BaseComponent.h"
#include "HelperStructs.h"
#include "TimerCallback.h"

enum class EnemyState
{
	searching,
	wander,
	shooting
};

class Timer;
class TimerCallBack;
class Player;
class EnemyLogic final : public BaseComponent
{
public:
	EnemyLogic(float speed, int score, int hp, const std::vector<Player*>& players);
	EnemyLogic(const EnemyLogic&) = delete;
	EnemyLogic& operator=(const EnemyLogic&) = delete;
	EnemyLogic(EnemyLogic&&) = delete;
	EnemyLogic& operator=(EnemyLogic&&) = delete;
	~EnemyLogic();

	int GetScore()const { return m_Score; };
	Vector2 GetDirection()const { return m_Direction; };
protected:
	void Initialize() override;
	void Update()override;
private:
	int m_Score{};
	float m_Speed{};
	int m_Hitpoints{};
	EnemyState m_EnemyState{ EnemyState::searching };

	Vector2 m_Direction{};

	TimerCallback* m_pTimerCallBack{ nullptr };
	Timer* m_pTimer{ nullptr };

	std::vector<Player*> m_pPlayers{};
};