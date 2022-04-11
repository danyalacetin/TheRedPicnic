// COMP710 GP 2D Framework 2019

// This include:
#include "splashscreen.h"

// Local includes:
#include "sprite.h"
#include "game.h"
#include "texture.h"

// Library includes:
#include <cassert>
#include <SDL_image.h>

SplashScreen::SplashScreen()
{
}


SplashScreen::~SplashScreen()
{
}

bool
SplashScreen::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;
	m_pSprite->SetHeight(m_pSprite->GetHeight() / Game::m_screenScaleRatio);
	m_pSprite->SetWidth(m_pSprite->GetWidth() / Game::m_screenScaleRatio);
	m_pSprite->SetAlpha(0);
	m_fTime = 0;
	m_maxDuration = 4.0f;
	m_holdDuration = 2.0f;
	m_finished = false;

	assert(m_holdDuration <= m_maxDuration);

	return (true);
}

void
SplashScreen::Process(float deltaTime)
{
	m_fTime += deltaTime;

	float fFractionalTime = m_fTime / m_maxDuration;

	float fHoldFraction = m_holdDuration / m_maxDuration;
	float fFadeDuration = (1.0f - fHoldFraction) / 2.0f;

	if (fFractionalTime <= fFadeDuration)
	{
		float fProgress = fFractionalTime / fFadeDuration;
		m_pSprite->SetAlpha(static_cast<int>(fProgress * 255.0f));

		// fade in
	}
	else if (fFractionalTime <= fFadeDuration + fHoldFraction)
	{
		m_pSprite->SetAlpha(255);
	}
	else if (fFractionalTime <= 1.0f)
	{
		float fProgress = (fFractionalTime - fFadeDuration - fHoldFraction) / fFadeDuration;
		m_pSprite->SetAlpha(static_cast<int>((1.0f - fProgress) * 255.0f));
		// fade out
	}
	else
	{
		m_pSprite->SetAlpha(0);
		m_finished = true;
	}
}

bool
SplashScreen::Isfinished()
{
	return m_finished;
}

void
SplashScreen::Setfinished()
{
	m_finished = true;
}

void
SplashScreen::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<int>(Game::m_screenDimensions.x / 2));
	m_pSprite->SetY(static_cast<int>(Game::m_screenDimensions.y / 2));


	m_pSprite->Draw(backBuffer);
}
