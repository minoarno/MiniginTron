#pragma once
#include "HelperStructs.h"
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
}

class Score;
class Lives;
class Player : public BaseComponent
{
public:
	Player(int lives);
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	Player(Player&&) = delete;
	Player& operator=(Player&&) = delete;
	~Player() = default;

	Score* GetScore();
	Lives* GetLives();

	Vector2 GetDirection()const { return m_DirectionBarrel; };
	void TurnLeft();
	void TurnRight();
protected:
	virtual void Initialize() override;
private:
	Score* m_pScore{ nullptr };
	Lives* m_pLives{ nullptr };
	int m_AmountOfLives{};

	Vector2 m_DirectionBarrel{0,1};
	float m_AngleInRadians{ 0.f };
	float m_RotationSpeed{ 20 };

	dae::GameObject* m_pBarrel;
};