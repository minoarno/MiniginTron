#include "TronPCH.h"
#include "MainMenu.h"

#include "FPSObject.h"
#include "PrefabBuilder.h"
#include "InputManager.h"
#include "TronCommands.h"

MainMenu::MainMenu()
	:dae::Scene{ "MainMenu" }
{
}

void MainMenu::Initialize()
{
	AddObject(Prefab::CreateButton({ 100, 60,200,60 }, new SceneSwapCommand{ 1 }, "UISingle.png"));
	AddObject(Prefab::CreateButton({ 100,120,200,60 }, new SceneSwapCommand{ 2 }, "UICoop.png"));
	AddObject(Prefab::CreateButton({ 100,180,200,60 }, new SceneSwapCommand{ 3 }, "UIVersus.png"));
}
