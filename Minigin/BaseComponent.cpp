#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "GameObject.h"

void BaseComponent::BaseInitialize()
{
	if (m_IsInitialized) return;
	Initialize();
	m_IsInitialized = true;
}
