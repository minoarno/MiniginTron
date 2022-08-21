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
	dae::GameObject* pFPSObject = AddObject(new dae::GameObject{});
	pFPSObject->AddComponent(new FPSObject{});
	pFPSObject->SetPosition(50, 50);

	AddObject(Prefab::CreatePlayer({100,50}, 0, this));

	AddObject(Prefab::CreateLevel("Level1.json", this));
}
