#include "TronPCH.h"
#include "MainMenu.h"

#include "FPSObject.h"
#include "PrefabBuilder.h"

#include "RigidBody.h"
#include "BoxCollider.h"

MainMenu::MainMenu()
	:dae::Scene{ "MainMenu" }
{
}

void MainMenu::Initialize()
{
	dae::GameObject* pFPSObject = AddObject(new dae::GameObject{});
	pFPSObject->AddComponent(new FPSObject{});
	pFPSObject->SetPosition(50, 50);

	dae::GameObject* pPlayer = AddObject(Prefab::CreatePlayer({100,50}, 0, this));
	pPlayer->AddComponent(new RigidBody(false));
	pPlayer->AddComponent(new BoxCollider({ 40,40 }, { 20, 20 }));

	AddObject(Prefab::CreateLevel("Level1.json", this));
}
