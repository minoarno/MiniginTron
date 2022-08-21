#include "MiniginPCH.h"
#include "Button.h"

#include "Command.h"

#include "GameObject.h"
#include "HelperFunctions.h"

Button::Button(const Vector2& dimensions, Command* pCommand)
	: BaseComponent{ }
	, m_pCommand{ pCommand }
	, m_Dimensions{ dimensions }
{
}

Button::~Button()
{
	delete m_pCommand;
	m_pCommand = nullptr;
}

Rect Button::GetHitbox() const
{
	auto pos = m_pGameObject->GetComponent<dae::Transform>()->GetWorldPosition();
	return Rect(pos.x,pos.y,m_Dimensions.x,m_Dimensions.y);
}

void Button::Click(const Vector2& mousePos)
{
	if (IsOverlapping(GetHitbox(),mousePos))
	{
		m_pCommand->Execute();
	}
}
