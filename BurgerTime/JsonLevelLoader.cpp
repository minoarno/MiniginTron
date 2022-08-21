#include "TronPCH.h"
#include "JsonLevelLoader.h"


#include <iostream>

#include "ResourceManager.h"
#include <fstream>

#include "PrefabBuilder.h"

#include "HighScore.h"

void JsonLevelLoader::LoadSceneUsingJson(dae::GameObject* pLevelObject, const std::string& jsonFile)
{
	auto posLevel = pLevelObject->GetComponent<dae::Transform>()->GetLocalPosition();

	nlohmann::json j = LoadJsonFile(jsonFile);
	
	dae::Scene* pScene = pLevelObject->GetScene();

	auto level = j.at("Level").get<std::vector<std::vector<int>>>();
	int blockWidth = j.at("BlockWidth").get<int>();
	int blockHeight = j.at("BlockHeight").get<int>();
	
	for (int r = 0; r < int(level.size()); r++)
	{
		for (int c = 0; c < int(level[r].size()); c++)
		{
			LevelBlockID id = LevelBlockID(level[r][c]);
			if (id != LevelBlockID::empty)
			{
				dae::GameObject* pLevelBlock = pLevelObject->AddChild(Prefab::CreateBlock(Vector2{ c * blockWidth, r * blockHeight}, Vector2{blockWidth,blockHeight}, pScene));
				pLevelBlock->SetTag("Level");
			}
		}
	}
}

nlohmann::json JsonLevelLoader::LoadJsonFile(const std::string& jsonFile)
{
	std::ifstream inputFile{dae::ResourceManager::GetInstance().GetDataPath() + jsonFile};
	
	nlohmann::json j;
	inputFile >> j;
	return j;
}

void JsonLevelLoader::LoadHighScore(const std::string& jsonFile, HighScore* pHighScoreList)
{
	nlohmann::json j = LoadJsonFile(jsonFile);

	auto highscoreList = j.at("HighScore").get<std::vector<int>>();
	for (size_t i = 0; i < highscoreList.size(); i++)
	{
		pHighScoreList->AddScore(highscoreList[i]);
	}
}
