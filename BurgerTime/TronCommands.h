#pragma once
#include "Command.h"
#include "GameObject.h"
#include "HelperStructs.h"
#include "Scene.h"
#include "EngineTime.h"
#include "Transform.h"
#include "RigidBody.h"

class MoveCommand : public Command
{
public:
	MoveCommand(dae::GameObject* pGameObject, float speed, const Vector2& dir = {})
		: m_pGameObject{ pGameObject }
		, m_Speed{ speed }
		, m_Direction{ dir }
	{
	}
	MoveCommand(const MoveCommand&) = delete;
	MoveCommand& operator=(const MoveCommand&) = delete;
	MoveCommand(MoveCommand&&) = delete;
	MoveCommand& operator=(MoveCommand&&) = delete;
	virtual ~MoveCommand() = default;

	virtual void Execute() const
	{
		float speed = m_Speed * float(Time::GetInstance().GetElapsedSeconds());
		auto pRigid = m_pGameObject->GetComponent<RigidBody>();
		pRigid->Move(m_Direction.x * speed, m_Direction.y * speed);
	}

	void SetDirection(const Vector2& dir) { m_Direction = dir; };

protected:
	Vector2 m_Direction{};
	dae::GameObject* m_pGameObject{};
	float m_Speed{ 20.f };
};