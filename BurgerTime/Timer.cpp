#include "BurgerTimePCH.h"
#include "Timer.h"
#include "EngineTime.h"

Timer::Timer(float duration, bool isCountingFromTheStart)
	: EventSubject{}
	, m_Duration{ duration }
	, m_IsTimerCounting{ isCountingFromTheStart }
{
}

void Timer::Reset()
{
	m_Timer = 0.0;
}

void Timer::Update()
{
	if (!m_IsTimerCounting) return;
	
	m_Timer += Time::GetInstance().GetFixedElapsedSeconds();
		
	if (m_Timer > m_Duration)
	{
		m_Timer -= m_Duration;
		Notify(this);
	}
}
