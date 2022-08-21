#include "TronPCH.h"
#include "MainMenu.h"

#include "FPSObject.h"
#include "PrefabBuilder.h"

MainMenu::MainMenu()
	:dae::Scene{ "MainMenu" }
{
}

void MainMenu::Initialize()
{
	AddObject(Prefab::CreatePlayer({20,50}, 0, this));

	AddObject(Prefab::CreateLevel("Level1.json", this));

	AddObject(Prefab::CreateBlueTank({ 20,360 }, this));

	//HUD
	dae::GameObject* pFPSObject = AddObject(new dae::GameObject{});
	pFPSObject->AddComponent(new FPSObject{});
	pFPSObject->SetPosition(50, 50);
}
