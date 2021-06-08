// COMP710 GP 2D Framework 2019

// This include:
#include "background.h"

// Local includes:
#include "game.h"
#include "sprite.h"
#include "backbuffer.h"
#include "gameutils.h"

// Library includes:
#include <cassert>

Background::Background()
	: m_pBackgroundSprite(0)
	, m_pMidgroundSprite(0)
	, m_pGroundSprite(0)
{

}

Background::~Background()
{

}

bool
Background::Initialise(Sprite* backgroundSprite, Sprite* midgroundSprite, Sprite* groundSprite)
{
	m_pBackgroundSprite = backgroundSprite;
	m_pMidgroundSprite = midgroundSprite;
	m_pGroundSprite = groundSprite;

	for (int i = 0; i < 3; i++)
	{
		m_backgroundX[i] = 0;
		m_midgroundX[i] = 0;
		m_groundX[i] = 0;
	}

	Vector2f screen = Game::m_screenDimensions;

	//screen height / sprite height = ratio
	//Times both exsiting height and width to scale with screen resolution

	m_pBackgroundSprite->SetWidth(m_pBackgroundSprite->GetDimensions().x * (screen.y / m_pBackgroundSprite->GetDimensions().y));
	m_pBackgroundSprite->SetHeight(screen.y);
	m_pBackgroundSprite->SetY(screen.y/2);
	m_pBackgroundSprite->SetX(screen.x /2);
	
	m_pMidgroundSprite->SetWidth(m_pMidgroundSprite->GetDimensions().x * (screen.y / m_pMidgroundSprite->GetDimensions().y));
	m_pMidgroundSprite->SetHeight(screen.y);
	m_pMidgroundSprite->SetY(screen.y /2);
	m_pMidgroundSprite->SetX(screen.x / 2);

	m_pGroundSprite->SetWidth(m_pGroundSprite->GetDimensions().x * (screen.y / m_pGroundSprite->GetDimensions().y));
	m_pGroundSprite->SetHeight(screen.y);
	m_pGroundSprite->SetY(screen.y /2);
	m_pGroundSprite->SetX(screen.x / 2);
	return (true);
}

void
Background::Process(float deltaTime)
{
	if (m_groundX[0] <= -m_pGroundSprite->GetWidth())
	{
		m_groundX[0] = 0;
	}
	else if (m_groundX[0] >= 500)
	{
		m_groundX[0] = -m_pGroundSprite->GetWidth() + 500;
	}

	if (m_midgroundX[0] <= -m_pMidgroundSprite->GetWidth())
	{
		m_midgroundX[0] = 0;
	}
	else if (m_midgroundX[0] >= 500)
	{
		m_midgroundX[0] = -m_pMidgroundSprite->GetWidth() + 500;
	}

	if (m_backgroundX[0] <= -m_pBackgroundSprite->GetWidth())
	{
		m_backgroundX[0] = 0;
	}
	else if (m_backgroundX[0] >= 500)
	{
		m_backgroundX[0] = -m_pBackgroundSprite->GetWidth() + 500;
	}

	m_groundX[0] = m_groundX[0] + m_cameraVelocity * deltaTime;
	m_groundX[1] = m_groundX[0] + m_pGroundSprite->GetWidth();
	m_groundX[2] = m_groundX[0] - m_pGroundSprite->GetWidth();

	m_backgroundX[0] = m_backgroundX[0] + m_cameraVelocity * deltaTime / 3;
	m_backgroundX[1] = m_backgroundX[0] + m_pBackgroundSprite->GetWidth();
	m_backgroundX[2] = m_backgroundX[0] - m_pBackgroundSprite->GetWidth();

	m_midgroundX[0] = m_midgroundX[0] + m_cameraVelocity * deltaTime / 2;
	m_midgroundX[1] = m_midgroundX[0] + m_pMidgroundSprite->GetWidth();
	m_midgroundX[2] = m_midgroundX[0] - m_pMidgroundSprite->GetWidth();
}

void
Background::Draw(BackBuffer& backBuffer)
{

	assert(m_pBackgroundSprite);
	assert(m_pGroundSprite);
	assert(m_pMidgroundSprite);

	for (int i = 0; i < 3; i++)
	{
		m_pBackgroundSprite->SetX(static_cast<int>(m_backgroundX[i]));
		m_pBackgroundSprite->Draw(backBuffer);
	}

	for (int i = 0; i < 3; i++)
	{
		m_pMidgroundSprite->SetX(static_cast<int>(m_midgroundX[i]));
		m_pMidgroundSprite->Draw(backBuffer);
	}

	for (int i = 0; i < 3; i++)
	{
		m_pGroundSprite->SetX(static_cast<int>(m_groundX[i]));
		m_pGroundSprite->Draw(backBuffer);
	}

}

int
Background::GetBackgroundX(int i)
{
	return m_backgroundX[i];
}

void
Background::SetBackgroundX(int i, int x)
{
	m_backgroundX[i] = x;
}

int
Background::GetMidgroundX(int i)
{
	return m_midgroundX[i];
}

void
Background::SetMidgroundX(int i, int x)
{
	m_midgroundX[i] = x;
}

int
Background::GetGroundX(int i)
{
	return m_groundX[i];
}

void
Background::SetGroundX(int i, int x)
{
	m_groundX[i] = x;
}

void
Background::SetCameraVelocity(float f)
{
	m_cameraVelocity = f;
}