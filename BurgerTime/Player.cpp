#include "TronPCH.h"
#include "Player.h"

#include "Lives.h"
#include "Score.h"

#include "EngineTime.h"
#include "HelperFunctions.h"
#include "GameObject.h"

Player::Player(int lives)
    : m_pLives{ new Lives{lives} }
    , m_pScore{ new Score{ } }
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
}

void Player::TurnRight()
{
    float elapsedSec = float(Time::GetInstance().GetElapsedSeconds());

    m_AngleInRadians -= elapsedSec * m_RotationSpeed;
    m_DirectionBarrel = RotateVector(m_DirectionBarrel, m_AngleInRadians);
    //m_pBarrel->GetComponent<dae::Transform>().
}

void Player::Initialize()
{
    //m_pBarrel = m_pGameObject->AddChild(new dae::GameObject{});

}
