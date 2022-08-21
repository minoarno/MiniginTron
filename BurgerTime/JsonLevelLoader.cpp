#include "TronPCH.h"
#include "JsonLevelLoader.h"


#include <iostream>

#include "ResourceManager.h"
#include <fstream>

#include "Pathfinding.h"
#include "PrefabBuilder.h"

#include "HighScore.h"

void JsonLevelLoader::LoadSceneUsingJson(dae::GameObject* pLevelObject, const std::string& jsonFile, Pathfinding* pPathfinding)
{
	pPathfinding = nullptr;

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
				//pPathfinding->AddNode({ c * blockWidth, y * blockHeight });
			}
		}
	}
	
	//Loading in the pathfinding
	//for (int r = 0; r < int(level.size()); r++)
	//{
	//	for (int c = 0; c < int(level[r].size()); c++)
	//	{
	//		int height = (r / 2) * 2 * (pLevel->GetSlabBlockHeight() + pLevel->GetLadderBlockHeight()) + (r % 2 == 1) * pLevel->GetLadderBlockHeight();
	//		int width{ c * pLevel->GetBlockWidth() };
	//		int index = pPathfinding->GetNodeID({ c * pLevel->GetBlockWidth(), y });
	//		
	//		int weight{ 1 };
	//		if (c - 1 >= 0 && LevelBlock::LevelBlockID(level[r][c - 1]) != LevelBlock::LevelBlockID::empty)
	//		{
	//			pPathfinding->AddEdge(index, pPathfinding->GetNodeID(Vector2{ width - pLevel->GetBlockWidth(),height }), weight);
	//		}
	//		if (r - 1 >= 0 && LevelBlock::LevelBlockID(level[r - 1][c]) != LevelBlock::LevelBlockID::empty)
	//		{
	//			pPathfinding->AddEdge(index, pPathfinding->GetNodeID(Vector2{ width,((r - 1) / 2) * 2 * (pLevel->GetSlabBlockHeight() + pLevel->GetLadderBlockHeight()) + ((r - 1) % 2 == 1) * pLevel->GetLadderBlockHeight() }), weight);
	//		}
	//		if (c + 1 < int(level[r].size()) && LevelBlock::LevelBlockID(level[r][c + 1]) != LevelBlock::LevelBlockID::empty)
	//		{
	//			pPathfinding->AddEdge(index, pPathfinding->GetNodeID(Vector2{ width + pLevel->GetBlockWidth(),height }), weight);
	//		}
	//		if (r + 1 < int(level.size()) && LevelBlock::LevelBlockID(level[r + 1][c]) != LevelBlock::LevelBlockID::empty)
	//		{
	//			pPathfinding->AddEdge(index, pPathfinding->GetNodeID(Vector2{ width,((r + 1) / 2) * 2 * (pLevel->GetSlabBlockHeight() + pLevel->GetLadderBlockHeight()) + ((r + 1) % 2 == 1) * pLevel->GetLadderBlockHeight() }), weight);
	//		}
	//	}
	//}
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
