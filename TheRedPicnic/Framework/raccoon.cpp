// This include:
#include "Raccoon.h"

// Local includes:
#include "sprite.h"
#include "animatedsprite.h"

// Library includes:
#include <cassert>

Raccoon::Raccoon()
	: NonPlayableCharacter()
{
	m_maxVelocityX = m_maxVelocityX/2;
	m_maxVelocityY = m_maxVelocityY/2;
}


void
Raccoon::ProcessIdle(float deltaTime)
{
	m_state = WALKING;
}

void
Raccoon::ProcessWalking(float deltaTime)
{
	if (m_pSprite->GetFrameX() == 0)
	{
			m_pSprite->SetPause(false);
			m_pSprite->SetFrameX(m_pSprite->GetFrameWidth());
			m_pSprite->SetFrameY(0);
			m_animationWait = 0;
	}
}

void
Raccoon::ProcessRunning(float deltaTime)
{}

void
Raccoon::Tracking(Entity& e)
{
	if (e.GetPositionX() > m_x)
	{
		m_pSprite->SetFlipped(false);
		m_velocityX = m_maxVelocityX;
	}
	else if (e.GetPositionX() < m_x)
	{
		m_pSprite->SetFlipped(true);
		m_velocityX = -m_maxVelocityX;
	}
}