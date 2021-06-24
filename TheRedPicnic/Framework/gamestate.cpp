// This include:
#include "gamestate.h"

// Local includes:
#include "game.h"
#include "state.h"
#include "resourcemanager.h"
#include "inputhandler.h"
#include "playablecharacter.h"
#include "logmanager.h"
#include "spritemanager.h"
#include "background.h"
#include "nonplayablecharacter.h"
#include "camera.h"

// Library includes:
#include <cassert>

//static members:
int GameState::m_ground = 0;
float GameState::m_gravity = 0;
float GameState::m_playerBoundaryMin = 0;
float GameState::m_playerBoundaryMax = 0;

GameState::GameState()
	: State()
{
}

GameState::~GameState()
{
	delete m_pPlayer;
	m_pPlayer = nullptr;

	delete m_pEnemy;
	m_pEnemy = nullptr;

	delete m_pEnemy2;
	m_pEnemy2 = nullptr;

	Camera::DestroyInstance();
}

bool
GameState::Initialise()
{
	m_type = InGame;

	SetInputWait(50);

	m_ground = 140 * Game::m_screenScaleRatio;
	m_gravity = 650;
	m_playerBoundaryMax = 160 * Game::m_screenScaleRatio;
	m_playerBoundaryMin = 16 * Game::m_screenScaleRatio;

	Camera::CreateInstance();

	m_pPlayer = new PlayableCharacter();
	m_pPlayer->Initialise(ResourceManager::GetInstance().GetSpriteManager().GetSprite(PLAYER));
	m_pPlayer->SetPosition(30 * Game::m_screenScaleRatio, 140 * Game::m_screenScaleRatio);

	m_pEnemy = new NonPlayableCharacter();
	m_pEnemy->Initialise(ResourceManager::GetInstance().GetSpriteManager().GetSprite(BUNNY));
	m_pEnemy->SetPosition(70 * Game::m_screenScaleRatio, 140 * Game::m_screenScaleRatio);

	m_pEnemy2 = new NonPlayableCharacter();
	m_pEnemy2->Initialise(ResourceManager::GetInstance().GetSpriteManager().GetSprite(SQUIRREL));
	m_pEnemy2->SetPosition(140 * Game::m_screenScaleRatio, 140 * Game::m_screenScaleRatio);

	return (true);
}

void
GameState::Process(float deltaTime)
{
	ProcessInputWait();
	if (GetInputWait() == 0)
	{
		if (ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_ESCAPE))
		{
			Game::GetInstance().AddGameMenuState();
		}
		if (ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_UP))
		{
			if (m_pPlayer->IsGrounded() || m_pPlayer->GetDoubleJump())
			{
				m_pPlayer->SetVerticalVelocity(-m_pPlayer->GetMaxVerticalVelocity());
				m_pPlayer->SetDoubleJump(!m_pPlayer->GetDoubleJump());
				ResourceManager::GetInstance().GetInputHandler().SetKeyPressed(SDLK_UP, false);
			}
		}
		if (ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_RIGHT) && m_pPlayer->GetHorizontalVelocity() < m_pPlayer->GetMaxHorizontalVelocity())
		{
			m_pPlayer->SetHorizontalVelocity(m_pPlayer->GetHorizontalVelocity() + m_pPlayer->GetMaxHorizontalVelocity());
		}

		if (ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_LEFT) && m_pPlayer->GetHorizontalVelocity() > -m_pPlayer->GetMaxHorizontalVelocity())
		{
			m_pPlayer->SetHorizontalVelocity(m_pPlayer->GetHorizontalVelocity() - m_pPlayer->GetMaxHorizontalVelocity());
		}
		
		if (!ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_RIGHT) && !ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_LEFT))
		{
			m_pPlayer->SetHorizontalVelocity(0);
		}

	}

	Game::GetInstance().GetBackground()->Process(deltaTime);
	m_pPlayer->Process(deltaTime);

	m_pEnemy->Tracking(*m_pPlayer);
	m_pEnemy->Process(deltaTime);

	m_pEnemy2->Tracking(*m_pPlayer);
	m_pEnemy2->Process(deltaTime);
}

void
GameState::Draw(BackBuffer& backBuffer)
{
	m_pPlayer->Draw(backBuffer);
	m_pEnemy->Draw(backBuffer);
	m_pEnemy2->Draw(backBuffer);
}
