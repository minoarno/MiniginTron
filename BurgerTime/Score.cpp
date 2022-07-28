#include "BurgerTimePCH.h"
#include "Score.h"

Score::Score()
    : EventSubject{}
    , m_Score{}
{
}

void Score::IncreaseScore(int amount)
{
    m_Score += amount;
    Notify(this);
}

int Score::GetScore() const
{
    return m_Score;
}
