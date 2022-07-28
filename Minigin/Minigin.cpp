#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "EngineTime.h"
#include "ServiceLocator.h"

using namespace std;
using namespace std::chrono;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"2DAE14 - Arno Poppe - Programming 4 assignment - Tron",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
	ServiceLocator::Initialize();
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	ServiceLocator::Provide(new Audio());
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	ResourceManager::GetInstance().CleanUp();
	ServiceLocator::CleanUp();
	InputManager::GetInstance().CleanUp();

	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		double lag = 0.0f;

		time_point<high_resolution_clock> lastTime = high_resolution_clock::now();

		//sceneManager.InitializeActiveScene();

		bool doContinue = true;
		while (doContinue)
		{
			const time_point<high_resolution_clock> currentTime = high_resolution_clock::now();
			const double elapsed = duration_cast<duration<double>>(currentTime - lastTime).count();

			//Saves the current elapsed time inside of the time singleton.
			Time::GetInstance().SetElapsedSeconds(elapsed);
			double elapsedFromTime = Time::GetInstance().GetElapsedSeconds();
			lastTime = currentTime;
			lag += elapsedFromTime;

			doContinue = input.ProcessInput();

			while (lag >= MsPerFrame)
			{
				sceneManager.FixedUpdate();
				lag -= MsPerFrame;
			}
			sceneManager.Update();
			sceneManager.LateUpdate();

			renderer.Render();

			auto sleepTime = duration_cast<duration<double>>(currentTime + milliseconds(MsPerFrame) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
