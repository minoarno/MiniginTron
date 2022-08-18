#include "TronPCH.h"
#include "ScoreObserver.h"

#include "Score.h"
#include "TextComponent.h"

ScoreObserver::ScoreObserver(TextComponent* pTextComponent)
	:m_pTextComponent{ pTextComponent }
{
}

void ScoreObserver::SetTextComponent(TextComponent* pTextComponent)
{
	m_pTextComponent = pTextComponent;
}

void ScoreObserver::OnNotify(EventSubject* pEventSubject)
{
	Score* score = dynamic_cast<Score*>(pEventSubject);
	std::string temp = "Score: " + std::to_string(score->GetScore());
	m_pTextComponent->SetText(temp);
}
