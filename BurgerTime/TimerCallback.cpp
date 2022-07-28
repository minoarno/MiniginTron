#include "BurgerTimePCH.h"
#include "TimerCallback.h"

TimerCallback::TimerCallback(const std::function<void()>& func)
	:EventObserver{}
	, m_Func{ func }
{
}

void TimerCallback::OnNotify(EventSubject*)
{
	m_Func();
}
