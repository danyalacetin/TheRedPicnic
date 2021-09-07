// This include:
#include "playablecharacter.h"

// Local includes:
#include "sprite.h"
#include "animatedsprite.h"
#include "backbuffer.h"
#include "character.h"
#include "game.h"
#include "background.h"
#include "gamestate.h"
#include "logmanager.h"
#include "camera.h"

// Library includes:
#include <cassert>

PlayableCharacter::PlayableCharacter()
	: Character(),
	m_canDoubleJump(false)
{
	m_maxVelocityX = 250 * Game::m_screenScaleRatio / 6;
	m_maxVelocityY = 500 * Game::m_screenScaleRatio / 6;
}

void
PlayableCharacter::Process(float deltaTime)
{
	ProcessAnimation(deltaTime);
	m_x -= Camera::GetInstance().GetVelocity() * deltaTime;
	ProcessPlayerBoundryChecks(deltaTime);
	ProcessMovement(deltaTime);
	ProcessFlip();
	m_pSprite->Process(deltaTime);
}

void
PlayableCharacter::ProcessAnimation(float deltaTime)
{
	if (m_flashing)
	{
		ProcessFlash(deltaTime);
	}

	if (!m_grounded)
	{	//Pause Animation, Set Jumping SpriteSheet
		m_pSprite->SetPause(true);
		m_pSprite->SetFrameY(m_pSprite->GetFrameHeight());
		if (m_velocityY <= 150 && m_velocityY >= -150)
		{
			//Set Apex Frame
			m_pSprite->SetFrameX(m_pSprite->GetFrameWidth() * 4);
		}
		else if (m_velocityY >= 0)
		{	//Set Falling Frame
			m_pSprite->SetFrameX(m_pSprite->GetFrameWidth() * 5);
		}
		else if (m_velocityY < 0)
		{	//Set Jumping Frame
			m_pSprite->SetFrameX(m_pSprite->GetFrameWidth() * 3);
		}
	}
	else
	{
		m_canDoubleJump = true;

		if (m_velocityX != 0)
		{	//Animate Walking
			m_pSprite->SetFrameY(0);
			m_pSprite->SetPause(false);
		}
		else
		{	//Idle Frame
			m_pSprite->SetPause(true);
			m_pSprite->SetFrameX(0);
			m_pSprite->SetFrameY(m_pSprite->GetFrameHeight());
		}
	}
}

void
PlayableCharacter::ProcessPlayerBoundryChecks(float deltaTime)
{
	//ProccessPlayerBoundryCheck
	if (m_x > GameState::m_playerBoundaryMax)
	{
		m_x = GameState::m_playerBoundaryMax;
		Game::GetInstance().GetBackground()->SetCameraVelocity(-m_velocityX);
		Camera::GetInstance().SetVelocity(-m_velocityX);
	}
	else if (m_x < GameState::m_playerBoundaryMin)
	{
		m_x = GameState::m_playerBoundaryMin;
		Game::GetInstance().GetBackground()->SetCameraVelocity(-m_velocityX);
		Camera::GetInstance().SetVelocity(-m_velocityX);
	}
	else
	{
		Game::GetInstance().GetBackground()->SetCameraVelocity(0);
		Camera::GetInstance().SetVelocity(0);
	}
}

bool
PlayableCharacter::GetDoubleJump()
{
	return m_canDoubleJump;
}

void
PlayableCharacter::SetDoubleJump(bool b)
{
	m_canDoubleJump = b;
}

