#include "TronPCH.h"
#include "SingleplayerLevel.h"

#include "FPSObject.h"
#include "PrefabBuilder.h"
#include "InputManager.h"

#include "Player.h"
#include "Lives.h"
#include "Score.h"

SingleplayerLevel::SingleplayerLevel()
	:dae::Scene{ "SingleplayerLevel" }
{
}

void SingleplayerLevel::Initialize()
{
	InputDesc inputDescPlayer1{};
	dae::GameObject* pPlayer = AddObject(Prefab::CreatePlayer({ 20,50 }, inputDescPlayer1, this));

	AddObject(Prefab::CreateLevel("Level1.json", this));

	AddObject(Prefab::CreateBlueTank({ 20,360 }, this));

	//HUD
	dae::GameObject* pFPSObject = AddObject(new dae::GameObject{});
	pFPSObject->AddComponent(new FPSObject{});
	pFPSObject->SetPosition(50, 420);

	AddObject(Prefab::CreateLiveText({ 200,420 }, pPlayer->GetComponent<Player>()->GetLives()));
	AddObject(Prefab::CreateScoreText({ 400,420 }, pPlayer->GetComponent<Player>()->GetScore()));
}
