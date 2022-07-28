#pragma once
#include "EventSubject.h"
class Score : public EventSubject
{
public:
	Score();
	Score(const Score&) = delete;
	Score& operator=(const Score&) = delete;
	Score(Score&&) = delete;
	Score& operator=(Score&&) = delete;
	~Score() = default;

	void IncreaseScore(int amount);

	int GetScore()const;
private:
	int m_Score = 0;
};

