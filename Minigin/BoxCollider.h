#pragma once
#include "BaseComponent.h"
#include "HelperFunctions.h"

class BoxCollider final :  public BaseComponent
{
public:
	BoxCollider(const Vector2& dims);
	BoxCollider(int width, int height);
	BoxCollider(const BoxCollider&) = delete;
	BoxCollider& operator=(const BoxCollider&) = delete;
	BoxCollider(BoxCollider&&) = delete;
	BoxCollider& operator=(BoxCollider&&) = delete;
	~BoxCollider() = default;

	int GetWidth()const { return m_Width; };
	void SetWidth(int value) { m_Width = value; };
	int GetHeight()const { return m_Height; };
	void SetHeight(int value) { m_Width = value; };
	void SetDimensions(const Vector2& dims);
	void SetDimensions(int width, int height);

	Rect GetBoundaries()const;

	bool IsColliding(const Rect& other);
	bool IsColliding(BoxCollider* other);

	Vector2 GetFootPosition() const;
protected:
	void Update() override { MakeSureDimensionsAreValid(); }
private:
	int m_Width{};
	int m_Height{};

	void MakeSureDimensionsAreValid();
};
