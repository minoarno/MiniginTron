#include "BurgerTimePCH.h"
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

//Framework
#include "Minigin.h"
#include "SceneManager.h"
//Levels


#include "ResourceManager.h"

#include "JsonLevelLoader.h"

#include "MainMenu.h"
#include "SingleplayerLevel.h"

int main(int, char* []) 
{
	// Tell the resource manager where he can find the game data
	// Easier access for if the user wants to change the data directory
	dae::ResourceManager::GetInstance().Init("../Data/");

	dae::Minigin engine{};
	engine.Initialize();
	{
		//Please add your scenes here
		dae::SceneManager::GetInstance().AddScene(new MainMenu());
		dae::SceneManager::GetInstance().AddScene(new SingleplayerLevel());
	}
	engine.Run();
	return 0;
}