#pragma once
#include "Transform.h"
#include <vector>
#include <typeindex>
#include <string>
#include <functional>
#include "HelperStructs.h"
#include "Box2D.h"
class BaseComponent;
class TextureComponent;

enum class CollisionType
{
	BeginContact,
	EndContact,
	PreSolve,
	PostSolve
};

typedef std::function<void(b2Fixture*, b2Fixture*, b2Contact*, CollisionType)> CollisionCallback;
namespace dae
{
	class Scene;
	class GameObject final
	{
	public:
		void SetTexture(const std::string& filename, int amountOfCols = 1, int amountOfRows = 1);
		void SetPosition(float x, float y, float z = 0.0f);
		void SetPosition(const Vector2& pos);

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template<typename T>
		std::enable_if_t<std::is_base_of_v<BaseComponent, T>, T*> AddComponent(T* newComponent)
		{
			AddComponent_(newComponent);
			return newComponent;
		}

		template<typename T>
		std::enable_if_t<std::is_base_of_v<GameObject, T>, T*> AddChild(T* newChild)
		{
			AddChild_(newChild);
			return newChild;
		}

		void SetParent(GameObject* newParentObject);
		void RemoveChild(GameObject* childObject);

		void SetScene(Scene* pScene);
		Scene* GetScene();
		GameObject* GetParent() { return m_pParent; };
		GameObject* GetChild(int index);
		const std::vector<GameObject*>& GetChildren()const { return m_pChildren; };
		
		template<typename T>
		std::enable_if_t<std::is_base_of_v<BaseComponent, T>, T*> GetComponent() const;
		
		template<typename T>
		void SetComponent(std::enable_if_t<std::is_base_of_v<BaseComponent, T>, T*> value);

		void SetTag(const std::string& tag) { m_Tag = tag; };
		std::string GetTag()const { return m_Tag; };

		void SetActive(bool value) { m_IsActive = value; }
		bool GetActive()const { return m_IsActive; }

		void Collision(b2Fixture* pThisFixture, b2Fixture* pOtherFixture, b2Contact* pContact, CollisionType contactType);
		void AddCollisionCallback(const CollisionCallback& callback);
	private:
		dae::Scene* m_pScene;
		std::string m_Tag;
	
		bool m_IsActive{ true };
		bool m_IsInitialized{ false };
		TextureComponent* m_pTextureComponent;
		std::vector<BaseComponent*> m_pBaseComponents;
		std::vector<GameObject*> m_pChildren;
		GameObject* m_pParent = nullptr;

		friend class Scene;

		void AddChild_(GameObject* newChild);
		void AddComponent_(BaseComponent* newComponent);

		void BaseInitialize();
		void BaseFixedUpdate();
		void BaseUpdate();
		void BaseLateUpdate();
		void BaseRender()const;

		std::vector<CollisionCallback> m_CollisionCallbacks;
	};

	template<typename T>
	inline std::enable_if_t<std::is_base_of_v<BaseComponent, T>, T*> GameObject::GetComponent() const
	{
		for (BaseComponent* c : m_pBaseComponents)
		{
			if (typeid(T).name() == typeid(*c).name())
			{
				return reinterpret_cast<T*>(c);
			}
		}
		return nullptr;
	}

	template<typename T>
	inline void GameObject::SetComponent(std::enable_if_t<std::is_base_of_v<BaseComponent, T>, T*> value)
	{
		for (BaseComponent*& c : m_pBaseComponents)
		{
			if (typeid(T) == typeid(*c))
			{
				delete c;
				c = reinterpret_cast<BaseComponent*>(value);
				return;
			}
		}
		
	}
}
