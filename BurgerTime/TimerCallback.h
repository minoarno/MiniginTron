#pragma once
#include "EventObserver.h"
#include <functional>

class TimerCallback final : public EventObserver
{
public:
	TimerCallback(const std::function<void()>& func);
	TimerCallback(const TimerCallback&) = delete;
	TimerCallback& operator=(const TimerCallback&) = delete;
	TimerCallback(TimerCallback&&) = delete;
	TimerCallback& operator=(TimerCallback&&) = delete;
	~TimerCallback() = default;

	virtual void OnNotify(EventSubject* pEventSubject) override;

private:
	std::function<void()> m_Func;
};
