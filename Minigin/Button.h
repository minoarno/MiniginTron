#pragma once
#include "BaseComponent.h"
#include <functional>

class Command;
class Button: public BaseComponent
{
public:
	Button(Command* pCommand);
	~Button() = default;
	Button(const Button& other) = delete;
	Button(Button&& other) = delete;
	Button& operator=(const Button& other) = delete;
	Button& operator=(Button&& other) = delete;

protected:
	Command* m_pCommand;
};

