#pragma once
#include "GameObject.h"
#include "HelperStructs.h"

namespace dae
{
	class Scene;
}
class Command;

namespace Prefab
{
	dae::GameObject* CreatePlayer(const Vector2& pos, DWORD playerIndex, dae::Scene* pScene);
	dae::GameObject* CreateButton(const Vector2& pos, Command* pCommand);
	dae::GameObject* CreateBlock(const Vector2& pos, const Vector2& dims, dae::Scene* pScene);
	dae::GameObject* CreateLevel(const std::string& filepath, dae::Scene* pScene);
}