#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Log.h"

void dae::SceneManager::FixedUpdate()
{
	m_pScenes[m_CurrentIndex]->BaseFixedUpdate();
}

void dae::SceneManager::Update()
{
	m_pScenes[m_CurrentIndex]->BaseUpdate();
}

void dae::SceneManager::LateUpdate()
{
	m_pScenes[m_CurrentIndex]->BaseLateUpdate();
}

void dae::SceneManager::Render()
{
	m_pScenes[m_CurrentIndex]->BaseRender();
}

void dae::SceneManager::NextScene()
{
	if (m_pScenes.size() > 1)
	{
		m_pScenes[m_CurrentIndex]->BaseUnload();
		m_CurrentIndex = ++m_CurrentIndex % m_pScenes.size();
	}
}


void dae::SceneManager::LoadScene(int index)
{
	if (index != m_CurrentIndex)
	{
		if (index >= 0 && index < int(m_pScenes.size()))
		{
			m_pScenes[m_CurrentIndex]->BaseUnload();
			m_CurrentIndex = index;
			m_pScenes[m_CurrentIndex]->BaseInitialize();
		}
		else
		{
			// out of range
			ME_CORE_WARN("The scene index is out of range");
		}
	}
	else
	{
		// Same scene
		ME_CORE_WARN("The scene is the same as the current one");
	}
}

dae::SceneManager::~SceneManager()
{
	for (size_t i = 0; i < m_pScenes.size(); i++)
	{
		delete m_pScenes[i];
		m_pScenes[i] = nullptr;
	}
	m_pScenes.clear();
}

dae::Scene* dae::SceneManager::AddScene(dae::Scene* pScene)
{
	m_pScenes.push_back(pScene);
	pScene->BaseInitialize();
	return pScene;
}

dae::Scene* dae::SceneManager::GetActiveScene() const
{
	return m_pScenes[m_CurrentIndex];
}

void dae::SceneManager::SetActiveScene(const int index)
{
	if (index < int(m_pScenes.size()))
	{
		if (index != m_CurrentIndex)
		{
			m_CurrentIndex = index;
			InitializeActiveScene();
		}
	}
	else
	{
		ME_CORE_WARN("Scene with index '{0}' not found. No new active scene has been set!", index );
	}
}

void dae::SceneManager::InitializeActiveScene()
{
	m_pScenes[m_CurrentIndex]->Initialize();
}
