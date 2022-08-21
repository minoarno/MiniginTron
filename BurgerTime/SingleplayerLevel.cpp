#include "TronPCH.h"
#include "SingleplayerLevel.h"

#include "FPSObject.h"
#include "PrefabBuilder.h"
#include "InputManager.h"

SingleplayerLevel::SingleplayerLevel()
	:dae::Scene{ "SingleplayerLevel" }
{
}

void SingleplayerLevel::Initialize()
{
	InputDesc inputDescPlayer1{};
	AddObject(Prefab::CreatePlayer({ 20,50 }, inputDescPlayer1, this));

	AddObject(Prefab::CreateLevel("Level1.json", this));

	AddObject(Prefab::CreateBlueTank({ 20,360 }, this));

	//HUD
	dae::GameObject* pFPSObject = AddObject(new dae::GameObject{});
	pFPSObject->AddComponent(new FPSObject{});
	pFPSObject->SetPosition(50, 450);
}
