#pragma once
#include "Scene.h"

class Audio;
class MainMenu : public dae::Scene
{
public:
	MainMenu();
	MainMenu(const MainMenu&) = delete;
	MainMenu& operator=(const MainMenu&) = delete;
	MainMenu(MainMenu&&) = delete;
	MainMenu& operator=(MainMenu&&) = delete;
	~MainMenu();

	virtual void Initialize();

private:
	Audio* m_pAudio;
};

