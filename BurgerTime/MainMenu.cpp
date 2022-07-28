#include "BurgerTimePCH.h"
#include "MainMenu.h"

#include "FPSObject.h"

MainMenu::MainMenu()
	:dae::Scene{ "MainMenu" }
{
}

void MainMenu::Initialize()
{
	dae::GameObject* pFPSObject = AddObject(new dae::GameObject{});
	pFPSObject->AddComponent(new FPSObject{});
	pFPSObject->SetPosition(50, 50);
}
