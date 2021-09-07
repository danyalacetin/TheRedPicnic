// This include:
#include "squirrel.h"

// Local includes:
#include "sprite.h"
#include "animatedsprite.h"

// Library includes:
#include <cassert>

Squirrel::Squirrel()
	: NonPlayableCharacter()
{

}

void
Squirrel::ProcessIdle(float deltaTime)
{
	m_state = WALKING;
}

void
Squirrel::ProcessWalking(float deltaTime)
{
	if (m_pSprite->GetFrameX() == 0)
	{
		if (m_animationWait >= 3)
		{
			m_pSprite->SetPause(false);
			m_pSprite->SetFrameX(m_pSprite->GetFrameWidth());
			m_pSprite->SetFrameY(0);
			m_animationWait = 0;
		}
		else if (m_grounded)
		{
			m_pSprite->SetPause(true);
			m_pSprite->SetFrameY(m_pSprite->GetFrameHeight());
			m_velocityX = 0;
			m_animationWait += deltaTime;
		}
	}
}

void
Squirrel::ProcessEating(float deltaTime)
{}

void
Squirrel::Tracking(Entity& e)
{
	if (m_animationWait >= 3)
	{
		if (e.GetPositionX() > m_x)
		{
			m_pSprite->SetFlipped(false);
		}
		else if (e.GetPositionX() < m_x)
		{
			m_pSprite->SetFlipped(true);
		}
	}
	else if (m_grounded)
	{
		if (m_pSprite->GetFlipped())
		{
			m_velocityX = -m_maxVelocityX;
		}
		else
		{
			m_velocityX = m_maxVelocityX;
		}
	}
}