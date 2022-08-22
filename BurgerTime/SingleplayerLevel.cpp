#include "TronPCH.h"
#include "SingleplayerLevel.h"

#include "FPSObject.h"
#include "PrefabBuilder.h"
#include "InputManager.h"

#include "Player.h"
#include "Lives.h"
#include "Score.h"

#include "EngineTime.h"
#include "HighScore.h"

SingleplayerLevel::SingleplayerLevel()
	:dae::Scene{ "SingleplayerLevel" }
{
	m_pHighScore = new HighScore{ "HighScore.json" };
}

SingleplayerLevel::~SingleplayerLevel()
{
	delete m_pHighScore;
	m_pHighScore = nullptr;
}

void SingleplayerLevel::Initialize()
{
	InputDesc inputDescPlayer1{};
	inputDescPlayer1.playerIndex = 0;
	dae::GameObject* pPlayerObject = AddObject(Prefab::CreatePlayer({ 20,50 }, inputDescPlayer1, this));
	std::vector<Player*> pPlayers{};
	pPlayers.emplace_back(pPlayerObject->GetComponent<Player>());
	m_pPlayer = pPlayerObject->GetComponent<Player>();

	AddObject(Prefab::CreateLevel("Level1.json", this));
	m_Respawns.emplace_back(Vector2{ 20,50 });
	m_Respawns.emplace_back(Vector2{ 200,50 });
	m_Respawns.emplace_back(Vector2{ 200,50 });

	AddObject(Prefab::CreateBlueTank({ 20,360 }, this, pPlayers));
	AddObject(Prefab::CreateBlueTank({ 400,360 }, this, pPlayers));
	AddObject(Prefab::CreateBlueTank({ 260,120 }, this, pPlayers));
	AddObject(Prefab::CreateRecognizer({ 200,360 }, this, pPlayers));
	AddObject(Prefab::CreateRecognizer({ 240,360 }, this, pPlayers));

	AddObject(Prefab::CreateDiamond({ 240,160 }, std::bind(&SingleplayerLevel::Respawn, this),this));

	//HUD
	dae::GameObject* pFPSObject = AddObject(new dae::GameObject{});
	pFPSObject->AddComponent(new FPSObject{});
	pFPSObject->SetPosition(50, 420);

	AddObject(Prefab::CreateLiveText({ 200,420 }, pPlayerObject->GetComponent<Player>()->GetLives()));
	AddObject(Prefab::CreateScoreText({ 400,420 }, pPlayerObject->GetComponent<Player>()->GetScore()));
}

void SingleplayerLevel::Update()
{
	if (m_pPlayer == nullptr)return;

	auto pLives = m_pPlayer->GetLives();
	if (pLives != nullptr && pLives->GetLives() <= 0)
	{
		Time::GetInstance().SetTimeScale(0.0);

		AddObject(Prefab::CreateHighScoreList({ 100, 40 }, "HighScore.json", m_pHighScore));
	}
}

void SingleplayerLevel::Respawn()
{
	if (m_Respawns.size() > 0)
	{
		m_pPlayer->GetGameObject()->SetPosition(m_Respawns[std::rand() % m_Respawns.size()]);
	}
}
