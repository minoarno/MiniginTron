#include "TronPCH.h"
#include "LiveObserver.h"

#include "Lives.h"
#include "TextComponent.h"

LiveObserver::LiveObserver(TextComponent* pTextComponent)
	:m_pTextComponent{ pTextComponent }
{
}

void LiveObserver::SetTextComponent(TextComponent* pTextComponent)
{
	m_pTextComponent = pTextComponent;
}

void LiveObserver::OnNotify(EventSubject* pEventSubject)
{
	Lives* lives = dynamic_cast<Lives*>(pEventSubject);
	std::string temp = "Lives: " + std::to_string(lives->GetLives());
	m_pTextComponent->SetText(temp);
}
