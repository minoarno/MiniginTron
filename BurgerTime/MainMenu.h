#pragma once
#include "Scene.h"
class MainMenu : public dae::Scene
{
public:
	MainMenu();
	MainMenu(const MainMenu&) = delete;
	MainMenu& operator=(const MainMenu&) = delete;
	MainMenu(MainMenu&&) = delete;
	MainMenu& operator=(MainMenu&&) = delete;
	~MainMenu() = default;

	virtual void Initialize();

private:
};

