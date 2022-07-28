#include "MiniginPCH.h"
#include "Transform.h"
#include "GameObject.h"

dae::Transform::Transform(const glm::vec3& pos)
	: BaseComponent{}
	, m_LocalPosition{pos}
{
}

glm::vec3 dae::Transform::GetWorldPosition() const
{
	glm::vec3 pos{};
	pos += m_LocalPosition;
	if (m_pGameObject->GetParent() != nullptr)
	{
		glm::vec3 parentPos{ m_pGameObject->GetParent()->GetComponent<dae::Transform>()->GetWorldPosition() };
		pos += parentPos;
	}
	return pos;
}

void dae::Transform::SetLocalPosition(const float x, const float y, const float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
}

void dae::Transform::Move(float x, float y, float z)
{
	m_LocalPosition.x += x;
	m_LocalPosition.y += y;
	m_LocalPosition.z += z;
}
