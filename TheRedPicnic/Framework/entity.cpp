// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"
#include "gamestate.h"
#include "game.h"
#include "camera.h"

// Library includes:
#include <cassert>

Entity::Entity()
: m_pSprite(0)
, m_x(0.0f)
, m_y(0.0f)
, m_velocityX(0.0f)
, m_velocityY(0.0f)
, m_maxVelocityX(0.0f)
, m_maxVelocityY(0.0f)
, m_dead(false)
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

	return (true);
}

void 
Entity::Process(float deltaTime)
{
	//Generic position update, based upon velocity (and time).

	//Boundary checking and position capping. 
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
	if (m_y >= GameState::m_ground)
	{
		m_y = GameState::m_ground;
		m_velocityY = 0;
		m_grounded = true;
	}
	else
	{
		m_velocityY += (GameState::m_gravity) * deltaTime * Game::m_screenScaleRatio / 6;
		m_grounded = false;
	}
}

bool
Entity::IsCollidingWith(Entity& e)
{

	return (false);
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
