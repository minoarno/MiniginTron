#include "MiniginPCH.h"
#include "Button.h"

#include "Command.h"

Button::Button(Command* pCommand)
	: BaseComponent{}
	, m_pCommand{pCommand}
{
}
