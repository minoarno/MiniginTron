#include "TronPCH.h"
#include "MainMenu.h"

#include "FPSObject.h"
#include "PrefabBuilder.h"
#include "InputManager.h"
#include "TronCommands.h"
#include "ServiceLocator.h"

MainMenu::MainMenu()
	:dae::Scene{ "MainMenu" }
{
	m_pAudio = new Audio{};
	ServiceLocator::Initialize();
	ServiceLocator::Provide(m_pAudio);
}

MainMenu::~MainMenu()
{
	delete m_pAudio;
	m_pAudio = nullptr;
}

void MainMenu::Initialize()
{
	AddObject(Prefab::CreateButton({ 160, 60,200,60 }, new SceneSwapCommand{ 1 }, "UISingle.png"));
	AddObject(Prefab::CreateButton({ 160,160,200,60 }, new SceneSwapCommand{ 2 }, "UICoop.png"));
	AddObject(Prefab::CreateButton({ 160,260,200,60 }, new SceneSwapCommand{ 3 }, "UIVersus.png"));


	//ServiceLocator::GetAudio().AddSound("Data/background.mp3");
	//ServiceLocator::GetAudio().PlaySoundW(0);
}
