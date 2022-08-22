#pragma once
#include <string>
#include <vector>
#include "GameObject.h"

class ContactListener;
class b2World;
class b2DebugDraw;
class Button;
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

		virtual void Initialize() = 0;
		
		virtual void FixedUpdate() {};
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void Render() const {};

		virtual void Unload() {};

		b2World* GetWorld();

	private: 
		friend class SceneManager;

		std::string m_Name;
		std::vector<GameObject*> m_pObjects{};
		std::vector<GameObject*> m_pToBeDeletedObjects{};

		b2World* m_pWorld{ nullptr };
		ContactListener* m_pContactListener{ nullptr };
		b2DebugDraw* m_pB2DebugDraw{ nullptr };

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
