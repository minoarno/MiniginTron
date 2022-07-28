#pragma once
#include "BaseComponent.h"

class TextComponent;
class FPSObject final : public BaseComponent
{
public:
	FPSObject();
	~FPSObject() = default;
	FPSObject(const FPSObject& other) = delete;
	FPSObject(FPSObject&& other) = delete;
	FPSObject& operator=(const FPSObject& other) = delete;
	FPSObject& operator=(FPSObject&& other) = delete;

	void Initialize() override;
	void Update() override;

private:
	double m_RefreshRate;
	double m_TotalTime;

	TextComponent* m_pTextComponent;
};

