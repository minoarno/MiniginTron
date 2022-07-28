#pragma once
#include "EventObserver.h"
class TextComponent;
class ScoreObserver : public EventObserver
{
public:
	ScoreObserver(TextComponent* pTextComponent);
	ScoreObserver(const ScoreObserver& other) = delete;
	ScoreObserver& operator=(const ScoreObserver& other) = delete;
	ScoreObserver(ScoreObserver&& other) = delete;
	ScoreObserver& operator=(ScoreObserver&& other) = delete;
	~ScoreObserver() = default;

	void SetTextComponent(TextComponent* pTextComponent);

	virtual void OnNotify(EventSubject* pEventSubject) override;
private:
	TextComponent* m_pTextComponent = nullptr;
};

