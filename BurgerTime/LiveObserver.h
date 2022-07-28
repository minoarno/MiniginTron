#pragma once
#include "EventObserver.h"

class TextComponent;
class LiveObserver : public EventObserver
{
public:
	LiveObserver(TextComponent* pTextComponent);
	LiveObserver(const LiveObserver& other) = delete;
	LiveObserver& operator=(const LiveObserver& other) = delete;
	LiveObserver(LiveObserver&& other) = delete;
	LiveObserver& operator=(LiveObserver&& other) = delete;
	~LiveObserver() = default;

	void SetTextComponent(TextComponent * pTextComponent);

	void OnNotify(EventSubject* pEventSubject) override;
private:
	TextComponent* m_pTextComponent = nullptr;
};

