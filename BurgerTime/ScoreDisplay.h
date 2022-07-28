#pragma once
#include "GameObject.h"
class Score;
class ScoreObserver;
class ScoreDisplay final: public BaseComponent
{
public:
	ScoreDisplay(Score* pScore);
	ScoreDisplay(const ScoreDisplay&) = delete;
	ScoreDisplay& operator=(const ScoreDisplay&) = delete;
	ScoreDisplay(ScoreDisplay&&) = delete;
	ScoreDisplay& operator=(ScoreDisplay&&) = delete;
	~ScoreDisplay();


	ScoreObserver* GetScoreObserver() { return m_pScoreObserver; };
protected:
	void Initialize()override;
private:
	ScoreObserver* m_pScoreObserver = nullptr;
};

