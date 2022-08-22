#include "TronPCH.h"
#include "MultiplayerLevel.h"

#include "Player.h"
#include "Lives.h"
#include "Score.h"

#include "EngineTime.h"
#include "HighScore.h"
#include "GameObject.h"
#include "PrefabBuilder.h"
#include "InputManager.h"

MultiplayerLevel::MultiplayerLevel()
	:dae::Scene{ "MultiplayerLevel" }
{
}

MultiplayerLevel::~MultiplayerLevel()
{
	delete m_pHighScore;
	m_pHighScore = nullptr;
}

void MultiplayerLevel::Initialize()
{
	InputDesc inputDescPlayer1{};
	inputDescPlayer1.playerIndex = 0;
	dae::GameObject* pPlayerObject = AddObject(Prefab::CreatePlayer({ 20,50 }, inputDescPlayer1, this));
	std::vector<Player*> pPlayers{};
	pPlayers.emplace_back(pPlayerObject->GetComponent<Player>());

	InputDesc inputDescPlayer2{};
	inputDescPlayer2.playerIndex = 1;
	dae::GameObject* pPlayerObject2 = AddObject(Prefab::CreatePlayer({ 240,50 }, inputDescPlayer2, this));
	pPlayers.emplace_back(pPlayerObject2->GetComponent<Player>());

	AddObject(Prefab::CreateLevel("Level1.json", this));
	m_Respawns.emplace_back(Vector2{ 20,50 });
	m_Respawns.emplace_back(Vector2{ 200,50 });
	m_Respawns.emplace_back(Vector2{ 200,50 });

	AddObject(Prefab::CreateBlueTank({ 20,360 }, this, pPlayers));
	AddObject(Prefab::CreateBlueTank({ 400,360 }, this, pPlayers));
	AddObject(Prefab::CreateBlueTank({ 260,120 }, this, pPlayers));
	AddObject(Prefab::CreateRecognizer({ 200,360 }, this, pPlayers));
	AddObject(Prefab::CreateRecognizer({ 240,360 }, this, pPlayers));

	//HUD

	AddObject(Prefab::CreateLiveText({ 200,400 }, pPlayerObject->GetComponent<Player>()->GetLives()));
	AddObject(Prefab::CreateScoreText({ 400,400 }, pPlayerObject->GetComponent<Player>()->GetScore()));	
	AddObject(Prefab::CreateLiveText({ 200,440 }, pPlayerObject2->GetComponent<Player>()->GetLives()));
	AddObject(Prefab::CreateScoreText({ 400,440 }, pPlayerObject2->GetComponent<Player>()->GetScore()));
}