#pragma once
#include "TronPCH.h"
#include "HighScore.h"

#include "JsonLevelLoader.h"

HighScore::HighScore(const std::string& filepath)
{
	JsonLevelLoader::LoadHighScore(filepath, this);
}

void HighScore::AddScore(int score)
{
	m_HighScores.push_back(score);
	std::sort(m_HighScores.begin(), m_HighScores.end());
	if (m_HighScores.size() > 10) m_HighScores.pop_back();
}

void HighScore::WriteHighScoreListToFile()
{
	//JsonLevelLoader::
}
