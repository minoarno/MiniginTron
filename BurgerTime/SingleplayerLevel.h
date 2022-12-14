#pragma once
#include "Scene.h"

class HighScore;
class Player;
class SingleplayerLevel final: public dae::Scene
{
public:
	SingleplayerLevel();
	SingleplayerLevel(const SingleplayerLevel&) = delete;
	SingleplayerLevel& operator=(const SingleplayerLevel&) = delete;
	SingleplayerLevel(SingleplayerLevel&&) = delete;
	SingleplayerLevel& operator=(SingleplayerLevel&&) = delete;
	~SingleplayerLevel();

protected:
	void Initialize() override;
	void Update()override;

	std::vector<Vector2> m_Respawns{};
	Player* m_pPlayer{ nullptr };

	void Respawn();
	HighScore* m_pHighScore{ nullptr };
};