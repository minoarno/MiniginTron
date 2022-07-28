#pragma once
#include "BaseComponent.h"
#include <vector>

class EventObserver;

class EventSubject : public BaseComponent
{
public:
	EventSubject();
	~EventSubject() = default;

	EventSubject(const EventSubject& other) = delete;
	EventSubject& operator=(const EventSubject& other) = delete;
	EventSubject(EventSubject&& other) = delete;
	EventSubject& operator=(EventSubject&& other) = delete;
	
	template<typename T>
	std::enable_if_t<std::is_base_of_v<EventObserver, T>, T*> AddObserver(T* pObserver)
	{
		m_pObservers.emplace_back(pObserver);
		m_AmountObservers++;
		return pObserver;
	}

	void RemoveObserver(EventObserver* observer);
protected:
	void Notify(EventSubject* pBaseComponent);

private:
	int m_AmountObservers;
	std::vector<EventObserver*> m_pObservers{};
};

