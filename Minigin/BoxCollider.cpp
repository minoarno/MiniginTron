#include "MiniginPCH.h"
#include "BoxCollider.h"

#include "HelperFunctions.h"
#include "GameObject.h"

#include "TextureComponent.h"

BoxCollider::BoxCollider(const Vector2& dims)
	: BoxCollider(dims.x,dims.y)
{
}

BoxCollider::BoxCollider(int width, int height)
	: BaseComponent{}
	, m_Width{ width }
	, m_Height{ height }
{
}

void BoxCollider::SetDimensions(const Vector2& dims)
{
	SetDimensions(dims.x, dims.y);
}

void BoxCollider::SetDimensions(int width, int height)
{
	m_Width = width;
	m_Height = height;
}

Rect BoxCollider::GetBoundaries() const
{
	auto pos = m_pGameObject->GetComponent<dae::Transform>()->GetWorldPosition();
	return Rect(int(pos.x), int(pos.y),m_Width,m_Height);
}

bool BoxCollider::IsColliding(const Rect& other)
{
	return IsOverlapping(GetBoundaries(), other);
}

bool BoxCollider::IsColliding(BoxCollider* other)
{
	return IsColliding(other->GetBoundaries());
}

Vector2 BoxCollider::GetFootPosition() const
{
	auto pos = m_pGameObject->GetComponent<dae::Transform>()->GetWorldPosition();
	return Vector2(int(pos.x) + m_Width / 2, int(pos.y) + m_Height);
}

void BoxCollider::MakeSureDimensionsAreValid()
{
	if (m_Width == 0 || m_Height == 0)
	{
		m_Width = m_pGameObject->GetComponent<TextureComponent>()->GetDestinationRect().w;
		m_Height = m_pGameObject->GetComponent<TextureComponent>()->GetDestinationRect().h;
	}
}
