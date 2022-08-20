#pragma once
#pragma warning(push)
#pragma warning(disable : 26800)
#include "json.hpp"
#pragma warning(pop)

namespace dae
{
	class GameObject;
}

enum class LevelBlockID
{
	empty = 0,
	block = 1
};
class Level;
class Pathfinding;
namespace JsonLevelLoader
{
	void LoadSceneUsingJson(dae::GameObject* pLevelObject, const std::string& jsonFile, Pathfinding* pPathfinding);
	nlohmann::json LoadJsonFile(const std::string& jsonFile);
};