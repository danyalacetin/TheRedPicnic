// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"
#include "gamestate.h"
#include "game.h"
#include "camera.h"
#include "texture.h"

// Library includes:
#include <cassert>

Entity::Entity()
: m_pSprite(0)
, m_x(0.0f)
, m_y(0.0f)
, m_width(0)
, m_height(0)
, m_velocityX(0.0f)
, m_velocityY(0.0f)
, m_maxVelocityX(0.0f)
, m_maxVelocityY(0.0f)
, m_hidden(false)
, m_flashing(false)
, m_dead(false)
, m_pushed(false)
, m_grounded(false)
{

}

Entity::~Entity()
{

}

bool
Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	m_width = m_pSprite->GetWidth();
	m_height = m_pSprite->GetHeight();
	return (true);
}

void 
Entity::Process(float deltaTime)
{
	//Generic position update, based upon velocity (and time).

	//Boundary checking and position capping. 
}

void
Entity::ProcessFlash(float deltaTime)
{
	m_flashTime = m_flashTime - deltaTime*2;

	if (m_flashTime >= 5)
	{
		m_hidden = true;
	}
	else if (m_flashTime >= 4.5)
	{
		m_hidden = false;
	}
	else if (m_flashTime >= 4)
	{
		m_hidden = true;
	}
	else if (m_flashTime >= 3.5)
	{
		m_hidden = false;
	}
	else if (m_flashTime >= 3)
	{
		m_hidden = true;
	}
	else if (m_flashTime >= 2.5)
	{
		m_hidden = false;
	}
	else if (m_flashTime >= 2)
	{
		m_hidden = true;
	}
	else if (m_flashTime >= 1.5)
	{
		m_hidden = false;
	}
	else if (m_flashTime >= 1)
	{
		m_hidden = true;
	}
	else if (m_flashTime >= 0.5)
	{
		m_hidden = false;
	}

	if (m_flashTime <= 0)
	{
		m_flashing = false;
		m_hidden = false;
	}
}

void 
Entity::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
	m_pSprite->Draw(backBuffer);
}

void
Entity::ProcessMovement(float deltaTime)
{

	//ProccessCamera
	m_x += Camera::GetInstance().GetVelocity() * deltaTime;

	//ProccessXMovement
	m_x += m_velocityX * deltaTime;

	//proccessYMovement
	m_y += m_velocityY * deltaTime;

	//ProcessEntityGroundCheck
	if (m_y >= GameState::m_ground - m_height/2)
	{
		m_y = GameState::m_ground - m_height/2;
		m_velocityY = 0;
		m_grounded = true;
	}
	else
	{
		m_velocityY += (GameState::m_gravity) * deltaTime * Game::m_screenScaleRatio / 6;
		m_grounded = false;
	}

	//Process Pushed
	if (m_pushed)
	{
		if (m_velocityX > 150 || m_velocityX < -150)
		{
			//FIX THIS? ADD GAME SCREEN SCALE!
			m_velocityX *= 0.99;
		}
		else
		{
			m_velocityX = 0;
			m_pushed = false;
		}
	}
}

bool
Entity::IsCollidingWith(Entity& e)
{
	bool result = false;

	float e1centerX = GetPositionX();
	float e1centerY = GetPositionY() + m_height/2;

	float e2centerX = e.GetPositionX();
	float e2centerY = e.GetPositionY() + e.GetHeight()/2;

	float e1radi = m_width/2;
	float e2radi = e.GetWidth()/2;

	float hypotenuse = sqrt(pow(e2centerY - e1centerY, 2) + pow(e2centerX - e1centerX, 2));

	if (hypotenuse <= e1radi/2 + e2radi/2){
		result = true;
	}

	return (result);
}

void 
Entity::SetDead(bool dead)
{
	m_dead = dead;
}

void
Entity::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

void
Entity::SetPositionX(float x)
{
	m_x = x;
}

void
Entity::SetPositionY(float y)
{
	m_y = y;
}

float 
Entity::GetPositionX() const
{
	return (m_x);
}

float 
Entity::GetPositionY() const
{
	return (m_y);
}

void
Entity::SetWidth(float w)
{
	m_width = w;
}

float
Entity::GetWidth()
{
	return m_width;
}

void
Entity::SetHeight(float h)
{
	m_height = h;
}

float
Entity::GetHeight()
{
	return m_height;
}

float 
Entity::GetHorizontalVelocity() const
{
	return (m_velocityX);
}

float 
Entity::GetVerticalVelocity() const
{
	return (m_velocityY);
}

void 
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void 
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}

float
Entity::GetMaxHorizontalVelocity() const
{
	return (m_maxVelocityX);
}

float
Entity::GetMaxVerticalVelocity() const
{
	return (m_maxVelocityY);
}

void
Entity::SetMaxHorizontalVelocity(float x)
{
	m_maxVelocityX = x;
}

void
Entity::SetMaxVerticalVelocity(float y)
{
	m_maxVelocityY = y;
}

bool
Entity::IsGrounded()
{
	return m_grounded;
}

bool
Entity::IsPushed()
{
	return m_pushed;
}

void
Entity::SetPushed(bool b)
{
	m_pushed = b;
}

bool
Entity::IsFlashing()
{
	return m_flashing;
}

void
Entity::SetFlashing(bool b)
{
	m_flashing = b;
	m_flashTime = 5;
}