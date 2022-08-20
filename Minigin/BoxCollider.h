#pragma once
#include "HelperFunctions.h"
#include "ColliderComponent.h"

class BoxCollider final :  public ColliderComponent
{
public:
	BoxCollider(const Vector2& dim, const Vector2& center);
	BoxCollider(const BoxCollider&) = delete;
	BoxCollider& operator=(const BoxCollider&) = delete;
	BoxCollider(BoxCollider&&) = delete;
	BoxCollider& operator=(BoxCollider&&) = delete;
	~BoxCollider() = default;

protected:
	virtual void Initialize() override;
};