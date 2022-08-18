#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

#include "HelperFunctions.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name)
	: m_Name{ name }
	, m_pObjects{}
{
}

Scene::~Scene()
{
	for (GameObject* pObject : m_pObjects)
	{
		delete pObject;
		pObject = nullptr;
	}
	m_pObjects.clear();

	for (GameObject* pObject : m_pToBeDeletedObjects)
	{
		delete pObject;
		pObject = nullptr;
	}
	m_pToBeDeletedObjects.clear();
}

void dae::Scene::RemoveObject(GameObject* pObject)
{
	m_pToBeDeletedObjects.emplace_back(pObject);
}

void dae::Scene::AddObject_(GameObject* pObject)
{
	m_pObjects.emplace_back(pObject);
	pObject->SetScene(this);
	pObject->BaseInitialize();
}

void dae::Scene::BaseInitialize()
{
	if (m_IsInitialized) return;

	Initialize();

	for (GameObject* pObject : m_pObjects)
	{
		pObject->BaseInitialize();
	}

	m_IsInitialized = true;
}

void dae::Scene::BaseFixedUpdate()
{
	for (GameObject* pObject : m_pObjects)
	{
		pObject->BaseFixedUpdate();
	}

	FixedUpdate();
}

void dae::Scene::BaseUpdate()
{
	for (GameObject* pObject : m_pObjects)
	{
		pObject->BaseUpdate();
	}

	Update();
}

void dae::Scene::BaseLateUpdate()
{
	for (GameObject* pObject : m_pObjects)
	{
		pObject->BaseLateUpdate();
	}

	LateUpdate();

	for (int i = 0; i < int(m_pToBeDeletedObjects.size()); i++)
	{
		auto it = std::remove_if(m_pObjects.begin(), m_pObjects.end(), [=](dae::GameObject* pObject)
			{
				return pObject == m_pToBeDeletedObjects[i];
			});

		delete m_pToBeDeletedObjects.back();
		m_pToBeDeletedObjects.back() = nullptr;

		m_pObjects.erase(it);
	}
	m_pToBeDeletedObjects.clear();
}

void dae::Scene::BaseRender() const
{
	for (GameObject* pObject : m_pObjects)
	{
		pObject->BaseRender();
	}

	Render();
}

void dae::Scene::BaseUnload()
{

	Unload();
}