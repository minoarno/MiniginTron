#include "MiniginPCH.h"
#include "EventSubject.h"
#include "EventObserver.h"

EventSubject::EventSubject()
	: BaseComponent{ }
	, m_AmountObservers{ 0 }
{
}

void EventSubject::RemoveObserver(EventObserver* observer)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(),observer));
}

void EventSubject::Notify(EventSubject* pBaseComponent)
{
	for (int i = 0; i < m_AmountObservers; i++)
	{
		m_pObservers[i]->OnNotify(pBaseComponent);
	}
}