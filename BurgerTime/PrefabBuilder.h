#pragma once
#include "GameObject.h"
#include "HelperStructs.h"

namespace dae
{
	class Scene;
}
class Command;
struct InputDesc;
namespace Prefab
{
	dae::GameObject* CreatePlayer(const Vector2& pos, InputDesc inputDesc, dae::Scene* pScene);
	dae::GameObject* CreateButton(const Rect& pos, Command* pCommand, const std::string& filepath);
	dae::GameObject* CreateBlock(const Vector2& pos, const Vector2& dims, dae::Scene* pScene);
	dae::GameObject* CreateLevel(const std::string& filepath, dae::Scene* pScene);
	dae::GameObject* CreateBlueTank(const Vector2& pos, dae::Scene* pScene);
	dae::GameObject* CreateRecognizer(const Vector2& pos, dae::Scene* pScene);
	dae::GameObject* CreateBullet(const Vector2& pos, const Vector2& direction , dae::Scene* pScene, const std::string& tagBullet);
}