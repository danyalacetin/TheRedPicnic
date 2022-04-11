// This include:
#include "Raccoon.h"

// Local includes:
#include "sprite.h"
#include "animatedsprite.h"
#include "fooditem.h"
#include "gamestate.h"
#include "playablecharacter.h"

// Library includes:
#include <cassert>

Raccoon::Raccoon()
	: NonPlayableCharacter()
{
	m_maxVelocityX = m_maxVelocityX/2;
	m_maxVelocityY = m_maxVelocityY/2;
}

void
Raccoon::ProcessAnimation(float deltaTime)
{
	switch (m_state) 
	{
	case(WALKING):
		if (m_pSprite->GetFrameX() == 0)
		{
			m_pSprite->SetPause(false);
			m_pSprite->SetFrameX(m_pSprite->GetFrameWidth());
			m_pSprite->SetFrameY(0);
			m_animationWait = 0;
		}
		break;
	case(RUNNING):
		if (m_pSprite->GetFrameX() == 0)
		{
			m_pSprite->SetPause(false);
			m_pSprite->SetFrameX(m_pSprite->GetFrameWidth());
			m_pSprite->SetFrameY(m_pSprite->GetFrameHeight());
			m_animationWait = 0;
		}
		break;
	}
	m_pSprite->Process(deltaTime);
}

void
Raccoon::ProcessIdle(float deltaTime)
{
	m_state = WALKING;
}

void
Raccoon::ProcessWalking(float deltaTime)
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

	//track food. If no food, track player
}

void
Raccoon::ProcessRunning(float deltaTime)
{
	m_food->SetPositionX(GetPositionX() + m_pSprite->GetWidth()/4);
	m_food->SetPositionY(GetPositionY());

	m_pSprite->SetFlipped(false);
	m_velocityX = m_maxVelocityX;
}

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

void
Raccoon::FoodReached(FoodItem& food)
{
	m_food = &food;
	m_state = RUNNING;
	m_pSprite->SetFrameX(0);
	m_maxVelocityX *= 2;
}