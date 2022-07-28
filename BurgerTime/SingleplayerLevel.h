#pragma once
#include "Scene.h"
class SingleplayerLevel : public dae::Scene
{
public:
	SingleplayerLevel();
	SingleplayerLevel(const SingleplayerLevel&) = delete;
	SingleplayerLevel& operator=(const SingleplayerLevel&) = delete;
	SingleplayerLevel(SingleplayerLevel&&) = delete;
	SingleplayerLevel& operator=(SingleplayerLevel&&) = delete;
	~SingleplayerLevel() = default;


	virtual void Initialize();
};