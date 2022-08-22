#include "TronPCH.h"
#include "Player.h"

#include "Lives.h"
#include "Score.h"

#include "EngineTime.h"
#include "HelperFunctions.h"
#include "GameObject.h"
#include "TextureComponent.h"
Player::Player(int lives)
    : m_AmountOfLives{ lives }
    , m_pLives{ nullptr }
    , m_pScore{ nullptr }
{
}

Score* Player::GetScore()
{
    return m_pScore;
}

Lives* Player::GetLives()
{
    return m_pLives;
}

void Player::TurnLeft()
{
    float elapsedSec = float(Time::GetInstance().GetElapsedSeconds());

    m_AngleInRadians += elapsedSec * m_RotationSpeed;
    m_DirectionBarrel = RotateVector(m_DirectionBarrel, m_AngleInRadians);
    m_pBarrel->GetComponent<dae::Transform>()->SetRotation(m_AngleInRadians);
}

void Player::TurnRight()
{
    float elapsedSec = float(Time::GetInstance().GetElapsedSeconds());

    m_AngleInRadians -= elapsedSec * m_RotationSpeed;
    m_DirectionBarrel = RotateVector(m_DirectionBarrel, m_AngleInRadians);
    m_pBarrel->GetComponent<dae::Transform>()->SetRotation(m_AngleInRadians);
}

void Player::Initialize()
{
    m_pLives = m_pGameObject->AddComponent(new Lives{ m_AmountOfLives });
    m_pScore = m_pGameObject->AddComponent(new Score{ });

    m_pBarrel = m_pGameObject->AddChild(new dae::GameObject{});
    m_pBarrel->SetTexture("Barrel.png");
    m_pBarrel->GetComponent<TextureComponent>()->SetDestinationRectDimensions({20,8});
}
