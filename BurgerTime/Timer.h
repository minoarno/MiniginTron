#pragma once
#include "EventSubject.h"
class Timer : public EventSubject
{
public:
	Timer(float duration, bool isCountingFromTheStart = false);
	Timer(const Timer&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(Timer&&) = delete;
	virtual ~Timer() = default;

	void Reset();
	void SetIsTimerCounting(bool value) { m_IsTimerCounting = value; }
	bool IsTimerCounting()const { return m_IsTimerCounting; }
protected:
	virtual void Update() override;
private:
	double m_Timer{};
	double m_Duration{};
	bool m_IsTimerCounting{ false };
};

