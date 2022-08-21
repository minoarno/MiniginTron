#pragma once
#include "BaseComponent.h"
#include "Box2D.h"

class RigidBody final : public BaseComponent
{
public:
	RigidBody(bool isStatic);
	RigidBody(const RigidBody&) = delete;
	RigidBody& operator=(const RigidBody&) = delete;
	RigidBody(RigidBody&&) = delete;
	RigidBody& operator=(RigidBody&&) = delete;
	~RigidBody();

	b2Fixture* AddCollider(const b2FixtureDef& fixtureDef);
	void Move(const float x, const float y);
protected:
	void Initialize() override;
	void Update() override;

private:
	b2Body* m_pBody{ nullptr };

	b2BodyDef m_BodyDef{};
};