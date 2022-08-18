#pragma once
#include "Command.h"
#include "GameObject.h"
#include "HelperStructs.h"
#include "Scene.h"
#include "EngineTime.h"
#include "Transform.h"

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
		auto trans = m_pGameObject->GetComponent<dae::Transform>();
		trans->Move(float(m_Direction.x) * speed, float(m_Direction.y) * speed, 0);
	}

	virtual void undo() const
	{
		float speed = m_Speed * float(Time::GetInstance().GetElapsedSeconds());
		m_pGameObject->GetComponent<dae::Transform>()->Move(float(-m_Direction.x) * speed, float(-m_Direction.y) * speed, 0);
	}

	void SetDirection(const Vector2& dir) { m_Direction = dir; };

protected:
	Vector2 m_Direction{};
	dae::GameObject* m_pGameObject{};
	float m_Speed{ 20.f };
};