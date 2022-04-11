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
#include "fooditem.h"
#include "gamestate.h"
#include "playablecharacter.h"
#include "resourcemanager.h"
#include "spritemanager.h"

// Library includes:
#include <cassert>

NonPlayableCharacter::NonPlayableCharacter()
	: Character()
{
	m_maxVelocityX = 250 * Game::m_screenScaleRatio / 6;
	m_maxVelocityY = 500 * Game::m_screenScaleRatio / 6;
	m_animationWait = ((rand() % 4));
	m_animationWaitDuration = ((rand() % 5) + 2);
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

	ProcessCollisionDetection(deltaTime);
	ProcessAnimation(deltaTime);
	ProcessMovement(deltaTime);
	ProcessFlip();

	for (FoodItem* pFood : GameState::m_pFoodItemContainer)
	{
		if (IsCollidingWith(*pFood) && GetState() != RUNNING)
		{
			FoodReached(*pFood);
		}
	}
}

void
NonPlayableCharacter::ProcessCollisionDetection(float deltaTime)
{
	if (IsCollidingWith(*GameState::m_pPlayer) && !GameState::m_pPlayer->IsFlashing())
	{
		FoodItem* pFood = new FoodItem();
		switch ((rand() % 4) + 1)
		{
		case 1:
			pFood->Initialise(ResourceManager::GetInstance().GetSpriteManager().GetSprite(APPLE));
			break;
		case 2:
			pFood->Initialise(ResourceManager::GetInstance().GetSpriteManager().GetSprite(CHICKEN));
			break;
		case 3:
			pFood->Initialise(ResourceManager::GetInstance().GetSpriteManager().GetSprite(MUFFIN));
			break;
		case 4:
			pFood->Initialise(ResourceManager::GetInstance().GetSpriteManager().GetSprite(PIE));
			break;
		}

		pFood->SetPosition(GameState::m_pPlayer->GetPositionX(), GameState::m_pPlayer->GetPositionY());
		pFood->SetPushed(true);
		pFood->SetVerticalVelocity(-GameState::m_pPlayer->GetMaxVerticalVelocity() / 2);
		GameState::m_pFoodItemContainer.push_back(pFood);

		GameState::m_pPlayer->SetFlashing(true);
		GameState::m_pPlayer->SetPushed(true);
		GameState::m_pPlayer->SetVerticalVelocity(-GameState::m_pPlayer->GetMaxVerticalVelocity());

		if (GetPositionX() >= GameState::m_pPlayer->GetPositionX())
		{
			GameState::m_pPlayer->SetHorizontalVelocity(-GameState::m_pPlayer->GetMaxHorizontalVelocity() * 2);
			pFood->SetHorizontalVelocity(GameState::m_pPlayer->GetMaxHorizontalVelocity() * 2);
		}
		else
		{
			GameState::m_pPlayer->SetHorizontalVelocity(GameState::m_pPlayer->GetMaxHorizontalVelocity() * 2);
			pFood->SetHorizontalVelocity(-GameState::m_pPlayer->GetMaxHorizontalVelocity() * 2);
		}
	}
}

void
NonPlayableCharacter::ProcessAnimation(float deltaTime)
{}

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

void
NonPlayableCharacter::FoodReached(FoodItem& food)
{
}


