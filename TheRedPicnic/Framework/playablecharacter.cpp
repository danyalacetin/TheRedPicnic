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

// Library includes:
#include <cassert>

PlayableCharacter::PlayableCharacter()
	: Character(),
	m_candoubleJump(false)
{

}

void
PlayableCharacter::Process(float deltaTime)
{
	ProcessAnimation(deltaTime);
	ProcessMovement(deltaTime);
	ProcessFlip();
	m_pSprite->Process(deltaTime);
}

void
PlayableCharacter::ProcessAnimation(float deltaTime)
{
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
		m_candoubleJump = true;

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

//--------------MOVE-MOVEMENT-TO-ENTITY-CLASS------------------

void
PlayableCharacter::ProcessMovement(float deltaTime)
{

	// X movement
	m_x += m_velocityX * deltaTime;

	if (m_x > GameState::m_playerBoundaryMax)
	{
		m_x = GameState::m_playerBoundaryMax;
		Game::GetInstance().GetBackground()->SetCameraVelocity(-m_velocityX);
	}
	else if (m_x < GameState::m_playerBoundaryMin)
	{
		m_x = GameState::m_playerBoundaryMin;
		Game::GetInstance().GetBackground()->SetCameraVelocity(-m_velocityX);
	}
	else
	{
		Game::GetInstance().GetBackground()->SetCameraVelocity(0);
	}

	//Y movement
	m_y += m_velocityY * deltaTime;

	if (m_y >= GameState::m_ground)
	{
		m_y = GameState::m_ground;
		m_velocityY = 0;
		m_grounded = true;
		m_candoubleJump = false;
	}
	else
	{
		m_velocityY += (GameState::m_gravity) * deltaTime * Game::m_screenScaleRatio / 6;
		m_grounded = false;
	}
}

//---------------------------------------------------------------


bool
PlayableCharacter::GetDoubleJump()
{
	return m_candoubleJump;
}

void
PlayableCharacter::SetDoubleJump(bool b)
{
	m_candoubleJump = b;
}

