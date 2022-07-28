#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		~SceneManager();

		Scene* AddScene(Scene* pScene);
		Scene* GetActiveScene()const;
		void SetActiveScene(const int index);

		void InitializeActiveScene();

		void FixedUpdate();
		void Update();
		void LateUpdate();

		void NextScene();
		void LoadScene(int index);
		
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<Scene*> m_pScenes;
		int m_CurrentIndex = 0;
	};
}
