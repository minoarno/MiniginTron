#pragma once
#include "BaseComponent.h"

class EventSubject;
class EventObserver
{
public:
	~EventObserver() = default;

	virtual void OnNotify(EventSubject* pEventSubject) = 0;
};

