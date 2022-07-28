#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

#include "BoxCollider.h"
#include "HelperFunctions.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name)
	: m_Name{ name }
	, m_pColliders{}
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

void dae::Scene::AddCollider(BoxCollider* pBoxCollider)
{
	m_pColliders.emplace_back(pBoxCollider);
}

std::vector<GameObject*> dae::Scene::CollisionDetection(GameObject* pObject) const
{
	std::vector<GameObject*> overlappingBoxColliders;

	BoxCollider* pBox = pObject->GetComponent<BoxCollider>();
	if (pBox == nullptr)
	{
		return overlappingBoxColliders;
	}

	for (int i = 0; i < int(m_pColliders.size()); i++)
	{
		if (pBox != m_pColliders[i])
		{
			BoxCollider* otherBox = m_pColliders[i];
			if (otherBox != nullptr)
			{
				if (pBox->IsColliding(otherBox))
				{
					overlappingBoxColliders.emplace_back(m_pColliders[i]->GetGameObject());
				}
			}
		}
	}

	return overlappingBoxColliders;
}

bool dae::Scene::CollisionDetectionOnTag(GameObject* pObject, const std::string& tag) const
{
	BoxCollider* pBox = pObject->GetComponent<BoxCollider>();
	if (pBox == nullptr)
	{
		return false;
	}

	return CollisionDetectionOnTag(pBox, tag);
}

bool dae::Scene::CollisionDetectionOnTag(GameObject* pObject, const std::string& tag, BoxCollider*& pFirstTaggedBox) const
{
	BoxCollider* pBox = pObject->GetComponent<BoxCollider>();
	if (pBox == nullptr)
	{
		return false;
	}

	return CollisionDetectionOnTag(pBox, tag, pFirstTaggedBox);
}

bool dae::Scene::CollisionDetectionOnTag(BoxCollider* pBox, const std::string& tag) const
{
	for (size_t i = 0; i < m_pColliders.size(); i++)
	{
		if (pBox != m_pColliders[i])
		{
			BoxCollider* otherBox = m_pColliders[i];
			if (otherBox != nullptr)
			{
				if (pBox->IsColliding(otherBox) && m_pColliders[i]->GetGameObject()->GetTag() == tag)
				{

					return true;
				}
			}
		}
	}

	return false;
}

bool dae::Scene::CollisionDetectionOnTag(BoxCollider* pBox, const std::string& tag, BoxCollider*& pFirstTaggedBox) const
{
	for (size_t i = 0; i < m_pColliders.size(); i++)
	{
		if (pBox != m_pColliders[i])
		{
			BoxCollider* otherBox = m_pColliders[i];
			if (otherBox != nullptr)
			{
				if (pBox->IsColliding(otherBox) && m_pColliders[i]->GetGameObject()->GetTag() == tag)
				{
					pFirstTaggedBox = otherBox;
					return true;
				}
			}
		}
	}
	pFirstTaggedBox = nullptr;
	return false;
}

bool dae::Scene::GroundDetectionOnTag(GameObject* pObject, const std::string& tag) const
{
	BoxCollider* pBox = pObject->GetComponent<BoxCollider>();
	if (pBox == nullptr)
	{
		return false;
	}

	return GroundDetectionOnTag(pBox, tag);
}

bool dae::Scene::GroundDetectionOnTag(BoxCollider* pBox, const std::string& tag) const
{
	for (size_t i = 0; i < m_pColliders.size(); i++)
	{
		if (pBox != m_pColliders[i])
		{
			BoxCollider* otherBox = m_pColliders[i];
			if (otherBox != nullptr)
			{
				if (IsOverlapping(otherBox->GetBoundaries(), pBox->GetFootPosition()) && m_pColliders[i]->GetGameObject()->GetTag() == tag)
				{
					return true;
				}
			}
		}
	}

	return false;
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
		BoxCollider* pBox = m_pToBeDeletedObjects[i]->GetComponent<BoxCollider>();
		if (pBox != nullptr)
		{
			auto colliderIt = std::remove_if(m_pColliders.begin(), m_pColliders.end(), [=](BoxCollider* pBoxElement)
				{
					return pBoxElement == pBox;
				});
			m_pColliders.erase(colliderIt);
		}

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