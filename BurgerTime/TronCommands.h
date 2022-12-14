#pragma once
#include "Command.h"
#include "GameObject.h"
#include "HelperStructs.h"
#include "Scene.h"
#include "SceneManager.h"
#include "EngineTime.h"
#include "Transform.h"
#include "RigidBody.h"
#include "PrefabBuilder.h"
#include "Player.h"
#include "EnemyLogic.h"

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

class ShootCommand : public Command
{
public:
	ShootCommand(dae::GameObject* pGameObject, float speed, const std::string& tagBullet)
		: m_pGameObject{ pGameObject }
		, m_Speed{ speed }
		, m_TagBullet{ tagBullet }
	{
	}
	ShootCommand(const ShootCommand&) = delete;
	ShootCommand& operator=(const ShootCommand&) = delete;
	ShootCommand(ShootCommand&&) = delete;
	ShootCommand& operator=(ShootCommand&&) = delete;
	~ShootCommand() = default;

	virtual void Execute() const
	{
		auto pPlayer = m_pGameObject->GetComponent<Player>();
		auto direction = pPlayer->GetDirection();

		auto pos = m_pGameObject->GetComponent<dae::Transform>()->GetWorldPosition();
		Vector2 position{ pos.x + direction.x * 20, pos.y + direction.y * 20 };
		
		m_pGameObject->GetScene()->AddObject(Prefab::CreateBullet(position, direction, m_pGameObject->GetScene(), m_TagBullet, pPlayer));
	}

	void SetDirection(const Vector2& dir) { m_Direction = dir; };
protected:
	Vector2 m_Direction{};
	dae::GameObject* m_pGameObject{};
	std::string m_TagBullet{};
	float m_Speed{ 24.f };
};

class RotateCommand : public Command
{
public:
	RotateCommand(dae::GameObject* pGameObject, bool turnLeft)
		: m_pGameObject{ pGameObject }
		, m_TurnLeft{ turnLeft }
	{
	}
	RotateCommand(const RotateCommand&) = delete;
	RotateCommand& operator=(const RotateCommand&) = delete;
	RotateCommand(RotateCommand&&) = delete;
	RotateCommand& operator=(RotateCommand&&) = delete;
	~RotateCommand() = default;

	virtual void Execute() const
	{
		if (m_TurnLeft)
		{
			m_pGameObject->GetComponent<Player>()->TurnLeft();
		}
		else
		{
			m_pGameObject->GetComponent<Player>()->TurnRight();
		}
	}

protected:
	dae::GameObject* m_pGameObject{};
	bool m_TurnLeft;
};

class SceneSwapCommand : public Command
{
public:
	SceneSwapCommand(int sceneIndex)
		: m_SceneIndex{sceneIndex}
	{
	}
	SceneSwapCommand(const SceneSwapCommand&) = delete;
	SceneSwapCommand& operator=(const SceneSwapCommand&) = delete;
	SceneSwapCommand(SceneSwapCommand&&) = delete;
	SceneSwapCommand& operator=(SceneSwapCommand&&) = delete;
	~SceneSwapCommand() = default;

	virtual void Execute() const
	{
		dae::SceneManager::GetInstance().SetActiveScene(m_SceneIndex);
	}

protected:
	int m_SceneIndex{};
};