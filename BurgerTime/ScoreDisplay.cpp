#include "TronPCH.h"
#include "ScoreDisplay.h"

#include "TextComponent.h"
#include "ResourceManager.h"
#include "ScoreObserver.h"
#include "Score.h"
ScoreDisplay::ScoreDisplay(Score* pScore)
	: m_pScore{pScore}
{
}

ScoreDisplay::~ScoreDisplay()
{
	delete m_pScoreObserver;
	m_pScoreObserver = nullptr;
}

void ScoreDisplay::Initialize()
{
	TextComponent* pText = m_pGameObject->GetComponent<TextComponent>();
	m_pScoreObserver = new ScoreObserver{ pText };
	m_pScore->AddObserver(m_pScoreObserver);
	pText->SetText("Score: 0");
}
