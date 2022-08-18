#include "TronPCH.h"
#include "LivesDisplay.h"

#include "GameObject.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "LiveObserver.h"
#include "Lives.h"

LivesDisplay::LivesDisplay(Lives* pLives)
{
	TextComponent* pText = new TextComponent{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	m_pLivesObserver = new LiveObserver(pText);
	m_pGameObject->AddComponent(pText);
	pLives->AddObserver(m_pLivesObserver);
	pText->SetText("Lives: 5");
}

LivesDisplay::~LivesDisplay()
{
	delete m_pLivesObserver;
	m_pLivesObserver = nullptr;
}

void LivesDisplay::Initialize()
{
}
