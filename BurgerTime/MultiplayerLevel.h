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
	~MultiplayerLevel();

protected:
	void Initialize() override;

	std::vector<Vector2> m_Respawns{};

	HighScore* m_pHighScore{ nullptr };
};