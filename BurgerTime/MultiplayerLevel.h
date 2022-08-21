#pragma once
#include "Scene.h"
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
};