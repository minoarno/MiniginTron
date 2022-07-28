#pragma once
#pragma warning(push)
#pragma warning(disable : 26800)
#include "json.hpp"
#pragma warning(pop)

class Level;
class Pathfinding;
namespace JsonLevelLoader
{
	void LoadSceneUsingJson(const std::string& jsonFile, Pathfinding* pPathfinding);
	nlohmann::json LoadJsonFile(const std::string& jsonFile);
};