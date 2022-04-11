// This include:
#include "bunny.h"

// Local includes:
#include "sprite.h"
#include "animatedsprite.h"
#include "gamestate.h"
#include "playablecharacter.h"

// Library includes:
#include <cassert>

Bunny::Bunny()
	: NonPlayableCharacter()
{

}

void
Bunny::ProcessAnimation(float deltaTime)
{
	switch (m_state)
	{
	case(WALKING):
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
		break;
	case(EATING):
		break;
	}
	m_pSprite->Process(deltaTime);
}

void
Bunny::ProcessIdle(float deltaTime)
{
	m_state = WALKING;
}

void
Bunny::ProcessWalking(float deltaTime)
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
Bunny::ProcessEating(float deltaTime)
{
}

void
Bunny::Tracking(Entity& e)
{
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

void
Bunny::FoodReached(FoodItem& food)
{
	if (m_pSprite->GetFrameX() == 0)
	{
		m_food = &food;
		m_state = EATING;
		m_pSprite->SetPause(true);
		m_pSprite->SetFrameY(m_pSprite->GetFrameHeight());
		m_velocityX = 0;
	}
}