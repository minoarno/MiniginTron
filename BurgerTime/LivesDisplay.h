#pragma once
#include "BaseComponent.h"
class Lives;
class LiveObserver;
class LivesDisplay : public BaseComponent
{
public:
	LivesDisplay(Lives* pLives);
	LivesDisplay(const LivesDisplay&) = delete;
	LivesDisplay& operator=(const LivesDisplay&) = delete;
	LivesDisplay(LivesDisplay&&) = delete;
	LivesDisplay& operator=(LivesDisplay&&) = delete;
	~LivesDisplay();

	LiveObserver* GetLivesObserver() { return m_pLivesObserver; };
protected:
	void Initialize()override;
private:
	LiveObserver* m_pLivesObserver = nullptr;
};

