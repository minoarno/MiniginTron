#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

#include "HelperFunctions.h"
#include "Box2D/Dynamics/b2World.h"
#include "ContactListener.h"
#include "b2DebugDraw.h"
#include "EngineTime.h"

#include "Log.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name)
	: m_Name{ name }
	, m_pObjects{}
	, m_pWorld{ new b2World{ {0,0}} }
{
	m_pWorld->SetAllowSleeping(false);
	m_pContactListener = new ContactListener{};
	m_pWorld->SetContactListener(m_pContactListener);

#if _DEBUG
	m_pB2DebugDraw = new b2DebugDraw();

	//enable all of the bitflags
	uint32 bitflags = 0;
	bitflags += b2Draw::e_shapeBit;
	bitflags += b2Draw::e_jointBit;
	bitflags += b2Draw::e_aabbBit;
	bitflags += b2Draw::e_pairBit;
	bitflags += b2Draw::e_centerOfMassBit;

	m_pB2DebugDraw->SetFlags(bitflags);
	m_pWorld->SetDebugDraw(m_pB2DebugDraw);
#endif
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

	delete m_pContactListener;
	m_pContactListener = nullptr;

	delete m_pWorld;
	m_pWorld = nullptr;

	delete m_pB2DebugDraw;
	m_pB2DebugDraw = nullptr;
}

void dae::Scene::RemoveObject(GameObject* pObject)
{
	if (std::find(m_pToBeDeletedObjects.begin(), m_pToBeDeletedObjects.end(),pObject) == m_pToBeDeletedObjects.end())
	{
		m_pToBeDeletedObjects.emplace_back(pObject);
	}
	else
	{
		ME_CORE_WARN("The item has already been added to the list");
	}
}

b2World* dae::Scene::GetWorld()
{
	return m_pWorld;
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
	m_pWorld->Step(float(Time::GetInstance().GetElapsedSeconds()), 10, 8);


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

	for (int i = int(m_pToBeDeletedObjects.size() - 1); i > 0; i--)
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