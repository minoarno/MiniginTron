#pragma once
#include <string>
#include <vector>
#include "GameObject.h"

class BoxCollider;
namespace dae
{
	class Scene
	{
	public:
		explicit Scene(const std::string& name);
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		virtual ~Scene();

		template<typename T>
		std::enable_if_t<std::is_base_of_v<GameObject, T>, T*> AddObject(T* pObject)
		{
			AddObject_(pObject);
			return pObject;
		}
		void RemoveObject(GameObject* pObject);

		void AddCollider(BoxCollider* pBoxCollider);

		virtual void Initialize() = 0;
		
		virtual void FixedUpdate() {};
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void Render() const {};

		virtual void Unload() {};

		std::vector<GameObject*> CollisionDetection(GameObject* pObject) const;
		bool CollisionDetectionOnTag(GameObject* pObject, const std::string& tag) const;
		bool CollisionDetectionOnTag(GameObject* pObject, const std::string& tag, BoxCollider*& pFirstTaggedBox) const;
		bool CollisionDetectionOnTag(BoxCollider* pBox, const std::string& tag) const;
		bool CollisionDetectionOnTag(BoxCollider* pBox, const std::string& tag, BoxCollider*& pFirstTaggedBox) const;
		bool GroundDetectionOnTag(GameObject* pObject, const std::string& tag) const;
		bool GroundDetectionOnTag(BoxCollider* pBox, const std::string& tag) const;
	private: 
		friend class SceneManager;

		std::string m_Name;
		std::vector<GameObject*> m_pObjects{};
		std::vector<GameObject*> m_pToBeDeletedObjects{};
		std::vector<BoxCollider*> m_pColliders{};

		bool m_IsInitialized{ false };

		static unsigned int m_IdCounter; 

		void AddObject_(GameObject* pObject);

		//Making sure that this gets done irregardless of what the user functions change
		void BaseInitialize();

		void BaseFixedUpdate();
		void BaseUpdate();
		void BaseLateUpdate();
		void BaseRender() const;

		void BaseUnload();
	};
}
