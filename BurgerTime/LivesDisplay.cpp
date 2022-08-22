#include "TronPCH.h"
#include "LivesDisplay.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "LiveObserver.h"
#include "Lives.h"

LivesDisplay::LivesDisplay(Lives* pLives)
	:m_pLives{pLives}
{
}

LivesDisplay::~LivesDisplay()
{
	delete m_pLivesObserver;
	m_pLivesObserver = nullptr;
}

void LivesDisplay::Initialize()
{
	TextComponent* pText = m_pGameObject->GetComponent<TextComponent>();
	m_pLivesObserver = new LiveObserver(pText);
	m_pLives->AddObserver(m_pLivesObserver);
	pText->SetText("Lives: 3");
}
