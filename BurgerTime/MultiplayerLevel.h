#pragma once
#include "Scene.h"

class HighScore;
class Player;
class MultiplayerLevel final : public dae::Scene
{
public:
	MultiplayerLevel();
	MultiplayerLevel(const MultiplayerLevel&) = delete;
	MultiplayerLevel& operator=(const MultiplayerLevel&) = delete;
	MultiplayerLevel(MultiplayerLevel&&) = delete;
	MultiplayerLevel& operator=(MultiplayerLevel&&) = delete;
	~MultiplayerLevel() = default;

protected:
	void Initialize() override;

	std::vector<Vector2> m_Respawns{};
	std::vector<dae::GameObject*> m_pEnemies{};
	dae::GameObject* m_pLevel{ nullptr };
	Player* m_pPlayer1{ nullptr };
	Player* m_pPlayer2{ nullptr };

	HighScore* m_pHighScore{ nullptr };
};