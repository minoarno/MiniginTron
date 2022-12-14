#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "Transform.h"
#include "TextureComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "RigidBody.h"

dae::GameObject::GameObject()
	: m_pTextureComponent{ nullptr }
	, m_pChildren{}
{
	AddComponent(new dae::Transform{});
}

dae::GameObject::~GameObject()
{
	for (BaseComponent* baseComponent : m_pBaseComponents)
	{
		delete baseComponent;
		baseComponent = nullptr;
	}
	m_pBaseComponents.clear();

	for (GameObject* child : m_pChildren)
	{
		delete child;
		child = nullptr;
	}
	m_pChildren.clear();
}

void dae::GameObject::SetParent(GameObject* newParentObject)
{
	if (this->m_pParent != nullptr)
	{
		//Detach it
		ME_CORE_ERROR("The object already has a parent");
		return;
	}

	if (this == newParentObject)
	{
		//LOGGER
		ME_CORE_ERROR("The gameobject and the child are the same!");
		return;
	}

	m_pParent = newParentObject;
}

void dae::GameObject::RemoveChild(GameObject* childObject)
{
	for (int i = int(m_pChildren.size()) - 1; i >= 0; i--)
	{
		if (m_pChildren[i] == childObject)
		{
			delete m_pChildren[i];
			m_pChildren[i] = nullptr;
			m_pChildren.erase(m_pChildren.begin() + i);
		}
	}
}

void dae::GameObject::SetScene(Scene* pScene)
{
	m_pScene = pScene;
	for (GameObject* pChild : m_pChildren)
	{
		pChild->SetScene(pScene);
	}
}

dae::Scene* dae::GameObject::GetScene()
{
	return m_pScene;
}

dae::GameObject* dae::GameObject::GetChild(int index)
{
	if (index >= int(m_pChildren.size()))
	{
		return nullptr;
	}

	return m_pChildren[index];
}

void dae::GameObject::Collision(b2Fixture* pThisFixture, b2Fixture* pOtherFixture, b2Contact* pContact, CollisionType contactType)
{
	for (size_t i = 0; i < m_CollisionCallbacks.size(); i++)
	{
		m_CollisionCallbacks[i](pThisFixture, pOtherFixture, pContact, contactType);
	}
}

void dae::GameObject::AddCollisionCallback(const CollisionCallback& callback)
{
	m_CollisionCallbacks.emplace_back(callback);
}

void dae::GameObject::AddChild_(GameObject* newChild)
{
	if (newChild->GetParent() != nullptr)
	{
		//LOGGER
		ME_CORE_ERROR("This gameobject already has a parent, try removing it first of it's parent");
		return;
	}

	if (this == newChild)
	{
		//LOGGER
		ME_CORE_ERROR("The gameobject and the child are the same!");
		return;
	}



	m_pChildren.emplace_back(newChild);
	newChild->SetScene(m_pScene);
	newChild->SetParent(this);
	newChild->BaseInitialize();
}

void dae::GameObject::AddComponent_(BaseComponent* newComponent)
{
	m_pBaseComponents.emplace_back(newComponent);
	newComponent->SetGameObject(this);
	newComponent->BaseInitialize();
}

void dae::GameObject::BaseInitialize()
{
	if (m_IsInitialized) return;

	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->BaseInitialize();
	}

	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->BaseInitialize();
	}

	m_IsInitialized = true;
}

void dae::GameObject::BaseFixedUpdate()
{
	if (!m_IsActive) return;

	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->FixedUpdate();
	}

	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->BaseFixedUpdate();
	}
}

void dae::GameObject::BaseUpdate()
{
	if (!m_IsActive) return;

	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->Update();
	}

	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->BaseUpdate();
	}
}

void dae::GameObject::BaseLateUpdate()
{
	if (!m_IsActive) return;

	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->LateUpdate();
	}

	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->BaseLateUpdate();
	}
}

void dae::GameObject::BaseRender() const
{
	if (!m_IsActive) return;

	const glm::vec3 pos = GetComponent<Transform>()->GetWorldPosition();
	if (m_pTextureComponent != nullptr)
	{
		Rect dstRect{ m_pTextureComponent->GetDestinationRect() };
		Rect srcRect{ m_pTextureComponent->GetSourceRect() };

		SDL_Rect dst = { int(pos.x), int(pos.y), int(dstRect.w), int(dstRect.h) };
		SDL_Rect src = { int(srcRect.x),int(srcRect.y),int(srcRect.w),int(srcRect.h) };
		if (src.w != 0 && src.h != 0)
		{
			if (dst.w != 0 && dst.h != 0)
			{
				Renderer::GetInstance().RenderTexture(m_pTextureComponent, src, dst, GetRotation());
			}
			else
			{
				Renderer::GetInstance().RenderTexture(m_pTextureComponent, src, dst.x, dst.y, GetRotation());
			}
		}
		else
		{
			Renderer::GetInstance().RenderTexture(m_pTextureComponent, dst.x, dst.y, GetRotation());
		}
	}

	for (size_t i = 0; i < m_pBaseComponents.size(); i++)
	{
		m_pBaseComponents[i]->Render();
	}

	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		m_pChildren[i]->BaseRender();
	}
}

float dae::GameObject::GetRotation() const
{
	return GetComponent<dae::Transform>()->GetRotation();
}

void dae::GameObject::SetTexture(const std::string& filename, int amountOfCols, int amountOfRows)
{
	if (m_pTextureComponent == nullptr)
	{
		m_pTextureComponent = AddComponent(new TextureComponent{ filename, amountOfCols, amountOfRows });
	}
	else m_pTextureComponent->SetTexture(filename);
	m_pTextureComponent->BaseInitialize();
	//m_pTextureComponent->CalculateSourceRect(amountOfCols,amountOfRows);
	//m_pTextureComponent->UpdateTexture();
}

void dae::GameObject::SetPosition(float x, float y, float z)
{
	GetComponent<Transform>()->SetLocalPosition( x, y, z);
}

void dae::GameObject::SetPosition(const Vector2& pos)
{
	GetComponent<Transform>()->SetLocalPosition(float(pos.x), float(pos.y), 0.f);
	//if (GetComponent<RigidBody>() != nullptr)
	//{
	//	GetComponent<RigidBody>()->GetBody()->SetTransform(b2Vec2{ pos.x, pos.y }, GetRotation());
	//}
}
