// This include:
#include "nonplayablecharacter.h"

// Local includes:
#include "sprite.h"
#include "animatedsprite.h"
#include "backbuffer.h"
#include "character.h"
#include "game.h"
#include "background.h"
#include "gamestate.h"
#include "logmanager.h"

// Library includes:
#include <cassert>

NonPlayableCharacter::NonPlayableCharacter()
	: Character()
{
	m_maxVelocityX = 250 * Game::m_screenScaleRatio / 6;
	m_maxVelocityY = 500 * Game::m_screenScaleRatio / 6;
	m_animationWait = 0;
}

void
NonPlayableCharacter::Process(float deltaTime)
{
	ProcessAnimation(deltaTime);
	ProcessMovement(deltaTime);
	ProcessFlip();
	m_pSprite->Process(deltaTime);
}

void
NonPlayableCharacter::ProcessAnimation(float deltaTime)
{
	if (m_pSprite->GetFrameX() == 0)
	{
		if (m_animationWait >= 3)
		{
			m_pSprite->SetPause(false);
			m_pSprite->SetFrameX(m_pSprite->GetFrameWidth());
			m_animationWait = 0;
		}
		else
		{
			m_pSprite->SetPause(true);
			m_velocityX = 0;
			m_animationWait += deltaTime;
		}
	}
}

void
NonPlayableCharacter::Tracking(Entity& e)
{
	if (!m_pSprite->IsPaused())
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
	else
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
}

