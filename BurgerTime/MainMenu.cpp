#include "TronPCH.h"
#include "MainMenu.h"

#include "FPSObject.h"
#include "PrefabBuilder.h"
#include "InputManager.h"

MainMenu::MainMenu()
	:dae::Scene{ "MainMenu" }
{
}

void MainMenu::Initialize()
{

	InputDesc inputDescPlayer1{};
	AddObject(Prefab::CreatePlayer({20,50}, inputDescPlayer1, this));

	AddObject(Prefab::CreateLevel("Level1.json", this));

	AddObject(Prefab::CreateBlueTank({ 20,360 }, this));

	//HUD
	dae::GameObject* pFPSObject = AddObject(new dae::GameObject{});
	pFPSObject->AddComponent(new FPSObject{});
	pFPSObject->SetPosition(50, 50);
}
