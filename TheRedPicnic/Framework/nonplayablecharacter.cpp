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
	m_state = IDLE;
}

void
NonPlayableCharacter::Process(float deltaTime)
{
	switch (m_state)
	{
	case IDLE:
		ProcessIdle(deltaTime);
		break;
	case WALKING:
		ProcessWalking(deltaTime);
		break;
	case RUNNING:
		ProcessRunning(deltaTime);
		break;
	case EATING:
		ProcessEating(deltaTime);
		break;

	default:
		break;
	}

	ProcessMovement(deltaTime);
	ProcessFlip();
	m_pSprite->Process(deltaTime);
}

void
NonPlayableCharacter::ProcessIdle(float deltaTime)
{}

void
NonPlayableCharacter::ProcessWalking(float deltaTime) 
{}

void
NonPlayableCharacter::ProcessRunning(float deltaTime) 
{}

void
NonPlayableCharacter::ProcessEating(float deltaTime) 
{}

void
NonPlayableCharacter::Tracking(Entity& e)
{}

void
NonPlayableCharacter::SetState(NpcState state)
{
	m_state = state;
}

NpcState 
NonPlayableCharacter::GetState()
{
	return m_state;
}


