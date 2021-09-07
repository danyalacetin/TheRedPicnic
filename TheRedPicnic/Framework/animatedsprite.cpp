// This includes:
#include "animatedsprite.h"

// Local includes:
#include "game.h"
#include "sprite.h"
#include "backbuffer.h"

AnimatedSprite::AnimatedSprite()
	: m_frameSpeed(0.2)
	, m_timeElapsed(0)
	, m_frameWidth(0)
	, m_frameHeight(0)
	, m_frameX(0)
	, m_frameY(0)
	, m_paused(true)
	, m_loop(false)
	, m_animating(false)
	, m_flipped(false)
{
}

AnimatedSprite::~AnimatedSprite()
{

}

bool
AnimatedSprite::Initialise(Sprite* sprite)
{
	m_sprite = sprite;
	m_frameWidth = 48;
	m_frameHeight = 48;
	m_width = m_frameWidth * Game::m_screenScaleRatio;
	m_height = m_frameHeight * Game::m_screenScaleRatio;

	StartAnimating();

	return (true);
}

void
AnimatedSprite::Process(float deltaTime)
{
	if (m_animating == true)
	{
		if (!m_paused)
		{
			m_timeElapsed += deltaTime;

			if (m_timeElapsed >= m_frameSpeed)
			{
				m_frameX += m_frameWidth;

				if (m_frameX >= m_sprite->GetWidth() / Game::m_screenScaleRatio)
				{
					m_frameX = 0;

					if (m_loop == false)
					{
						m_animating = false;
					}
				}
				m_timeElapsed = 0;
			}
		}
	}
}

void
AnimatedSprite::Draw(BackBuffer& backbuffer)
{
	backbuffer.DrawAnimatedSprite(*this);
}

Sprite*
AnimatedSprite::GetSprite()
{
	return m_sprite;
}

void
AnimatedSprite::SetWidth(int w)
{
	m_width = w;
}

void
AnimatedSprite::SetHeight(int h)
{
	m_height = h;
}

int
AnimatedSprite::GetWidth()
{
	return m_width;
}

int
AnimatedSprite::GetHeight()
{
	return m_width;
}

void
AnimatedSprite::SetFrameSpeed(float f)
{
	m_frameSpeed = f;
}

void
AnimatedSprite::SetFrameWidth(int w)
{
	m_frameWidth = w;
}

void
AnimatedSprite::SetFrameHeight(int h)
{
	m_frameHeight = h;
}

int
AnimatedSprite::GetFrameWidth()
{
	return m_frameWidth;
}

int
AnimatedSprite::GetFrameHeight()
{
	return m_frameHeight;
}

void AnimatedSprite::SetFrameX(int x)
{
	m_frameX = x;
}

void AnimatedSprite::SetFrameY(int y)
{
	m_frameY = y;
}

int AnimatedSprite::GetFrameX()
{
	return m_frameX;
}

int AnimatedSprite::GetFrameY()
{
	return m_frameY;
}

void
AnimatedSprite::SetPause(bool p)
{
	m_paused = p;
}

bool
AnimatedSprite::IsPaused()
{
	return (m_paused);
}

bool
AnimatedSprite::IsAnimating()
{
	return (m_animating);
}

void
AnimatedSprite::StartAnimating()
{
	m_animating = true;

	m_timeElapsed = 0;
	m_frameX = 0;
}

bool
AnimatedSprite::IsLooping()
{
	return (m_loop);
}

void
AnimatedSprite::SetLooping(bool b)
{
	m_loop = b;
}

void
AnimatedSprite::SetFlipped(bool b)
{
	m_flipped = b;
}

bool
AnimatedSprite::GetFlipped()
{
	return m_flipped;
}