#pragma once
#include "BaseComponent.h"
#include <functional>

class Diamond : public BaseComponent
{
public:
	Diamond(const std::function<void()>& func);
	Diamond(const Diamond&) = delete;
	Diamond& operator=(const Diamond&) = delete;
	Diamond(Diamond&&) = delete;
	Diamond& operator=(Diamond&&) = delete;
	~Diamond() = default;

protected:
	void Initialize()override;

	std::function<void()> m_Func;
};