#pragma once
#include "GameObject.h"
#include "HelperStructs.h"

class Command;
namespace Prefab
{
	dae::GameObject* CreatePlayer(const Vector2& pos);

	dae::GameObject* CreateButton(const Vector2& pos, Command* pCommand);
}