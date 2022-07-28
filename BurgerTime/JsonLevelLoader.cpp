#include "BurgerTimePCH.h"
#include "JsonLevelLoader.h"


#include <iostream>

#include "ResourceManager.h"
#include <fstream>

#include "Pathfinding.h"

void JsonLevelLoader::LoadSceneUsingJson(const std::string& jsonFile, Pathfinding* pPathfinding)
{
	nlohmann::json j = LoadJsonFile(jsonFile);

	pPathfinding = nullptr;

	//auto level = j.at("Level").get<std::vector<std::vector<int>>>();
	//pLevel->SetBlockWidth(j.at("ColWidthBlock").get<int>());
	//pLevel->SetSlabBlockHeight(j.at("SlabBlockHeight").get<int>());
	//pLevel->SetLadderBlockHeight(j.at("LadderBlockHeight").get<int>());
	//
	//int y{};
	//
	//for (int r = 0; r < int(level.size()); r++)
	//{
	//	int height{ (r % 2 == 0) ? pLevel->GetSlabBlockHeight() : pLevel->GetLadderBlockHeight() };
	//	for (int c = 0; c < int(level[r].size()); c++)
	//	{
	//		LevelBlock::LevelBlockID id = LevelBlock::LevelBlockID(level[r][c]);
	//		if (id != LevelBlock::LevelBlockID::empty)
	//		{
	//			LevelBlock* pLevelBlock = pLevel->AddChild(new LevelBlock{ id , Vector2{pLevel->GetBlockWidth(), height} });
	//			pLevelBlock->SetTag("Level");
	//			pLevelBlock->SetPosition(float(c * pLevel->GetBlockWidth()), float(y));
	//
	//			pPathfinding->AddNode({ c * pLevel->GetBlockWidth(), y });
	//		}
	//	}
	//	y += height;
	//}
	//
	////Loading in the pathfinding
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
