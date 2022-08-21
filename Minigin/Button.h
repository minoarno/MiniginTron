#pragma once
#include "BaseComponent.h"
#include <functional>
#include "HelperStructs.h"

class Command;
class Button: public BaseComponent
{
public:
	Button(const Vector2& dimensions, Command* pCommand);
	virtual ~Button();
	Button(const Button& other) = delete;
	Button(Button&& other) = delete;
	Button& operator=(const Button& other) = delete;
	Button& operator=(Button&& other) = delete;

	Rect GetHitbox()const;
	void Click(const Vector2& mousePos);

private:
	Command* m_pCommand;

	Vector2 m_Dimensions{};
};

