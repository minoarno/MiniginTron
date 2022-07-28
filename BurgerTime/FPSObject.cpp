#include "BurgerTimePCH.h"
#include "FPSObject.h"
#include "EngineTime.h"

#include "TextComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"

FPSObject::FPSObject()
	: BaseComponent{}
	, m_TotalTime{.9f}
	, m_RefreshRate{1.f}
	, m_pTextComponent{ nullptr }
{
}

void FPSObject::Initialize()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	m_pTextComponent = m_pGameObject->AddComponent(new TextComponent{ font, "FPS: 0" });
}

void FPSObject::Update()
{
	const double elapsedSec = Time::GetInstance().GetElapsedSeconds();
	m_TotalTime += elapsedSec;
	if (m_TotalTime >= m_RefreshRate)
	{
		const int fpsValue = static_cast<int>(1.0 / elapsedSec);
		m_pTextComponent->SetText("FPS: " + std::to_string(fpsValue));
		m_TotalTime -= m_RefreshRate;
	}
}
