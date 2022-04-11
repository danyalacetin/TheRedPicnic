// This include:
#include "squirrel.h"

// Local includes:
#include "sprite.h"
#include "animatedsprite.h"
#include "gamestate.h"
#include "playablecharacter.h"

// Library includes:
#include <cassert>

Squirrel::Squirrel()
	: NonPlayableCharacter()
{

}

void
Squirrel::ProcessAnimation(float deltaTime)
{
	if (m_pSprite->GetFrameX() == 0)
	{
		if (m_animationWait >= m_animationWaitDuration)
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
	m_pSprite->Process(deltaTime);
}

void
Squirrel::ProcessIdle(float deltaTime)
{
	m_state = WALKING;
}

void
Squirrel::ProcessWalking(float deltaTime)
{
	if (GameState::m_pFoodItemContainer.empty())
	{
		//If no food, track player
		Tracking(*GameState::m_pPlayer);
	}
	else
	{
		FoodItem* pFoodNearest = GameState::m_pFoodItemContainer.back();
		for (FoodItem* pFood : GameState::m_pFoodItemContainer)
		{
			float distance = pFood->GetPositionX() - GetPositionX();
			if (distance < 0)
			{
				distance *= -1;
			}

			float distance2 = pFoodNearest->GetPositionX() - GetPositionX();
			if (distance2 < 0)
			{
				distance2 *= -1;
			}

			if (distance < distance2)
			{
				pFoodNearest = pFood;
			}
		}
		//Otherwise, track closest food.
		Tracking(*pFoodNearest);
	}
}

void
Squirrel::ProcessEating(float deltaTime)
{}

void
Squirrel::Tracking(Entity& e)
{
	//Faces target just before movement, then stops tracking but moves in direction it's facing.

	//Faces target when animation begins (Just before movement)
	if (m_animationWait >= m_animationWaitDuration)
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
	//Moves in direction it's looking
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