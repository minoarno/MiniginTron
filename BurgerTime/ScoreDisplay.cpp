#include "TronPCH.h"
#include "ScoreDisplay.h"

#include "TextComponent.h"
#include "ResourceManager.h"
#include "ScoreObserver.h"
#include "Score.h"
ScoreDisplay::ScoreDisplay(Score* pScore)
{
	TextComponent* pText = new TextComponent{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	m_pGameObject->AddComponent(pText);
	m_pScoreObserver = new ScoreObserver{pText};
	pScore->AddObserver(m_pScoreObserver);
	pText->SetText("Score: 0");
}

ScoreDisplay::~ScoreDisplay()
{
	delete m_pScoreObserver;
	m_pScoreObserver = nullptr;
}

void ScoreDisplay::Initialize()
{
	
}
