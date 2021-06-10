// This include:
#include "playablecharacter.h"

// Local includes:
#include "sprite.h"
#include "animatedsprite.h"
#include "backbuffer.h"
#include "character.h"
#include "game.h"
#include "background.h"

// Library includes:
#include <cassert>

PlayableCharacter::PlayableCharacter()
	: Character()
	, m_borderMax(1000)
	, m_borderMin(100)
{

}

void
PlayableCharacter::Process(float deltaTime)
{
	if (/*!m_grounded*/false)
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
		m_doubleJump = true;
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

	m_x += m_velocityX * deltaTime;

	if (m_x > m_borderMax)
	{
		m_x = m_borderMax;
		Game::GetInstance().GetBackground()->SetCameraVelocity(-m_velocityX);
	}
	else if (m_x < m_borderMin)
	{
		m_x = m_borderMin;
		Game::GetInstance().GetBackground()->SetCameraVelocity(-m_velocityX);
	}
	else
	{
		Game::GetInstance().GetBackground()->SetCameraVelocity(0);
	}

	ProcessFlip();
	m_pSprite->Process(deltaTime);
}


bool
PlayableCharacter::GetDoubleJump()
{
	return m_doubleJump;
}

void
PlayableCharacter::SetDoubleJump(bool b)
{
	m_doubleJump = b;
}

int
PlayableCharacter::GetBorderMax()
{
	return m_borderMax;
}

int
PlayableCharacter::GetBorderMin()
{
	return m_borderMin;
}
