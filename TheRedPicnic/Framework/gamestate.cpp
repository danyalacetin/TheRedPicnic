// This include:
#include "gamestate.h"

// Local includes:
#include "game.h"
#include "state.h"
#include "resourcemanager.h"
#include "inputhandler.h"
#include "playablecharacter.h"
#include "resourcemanager.h"
#include "spritemanager.h"
#include "background.h"

// Library includes:
#include <cassert>

GameState::GameState()
	: State()
{
}

GameState::~GameState()
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

bool
GameState::Initialise()
{
	SetInputWait(50);

	m_pPlayer = new PlayableCharacter();
	m_pPlayer->Initialise(ResourceManager::GetInstance().GetSpriteManager().GetSprite(PLAYER));
	m_pPlayer->SetPosition(200, 850);

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
			/*if (m_pPlayer->IsGrounded() || m_pPlayer->GetDoubleJump())
			{
				m_pPlayer->SetVerticalVelocity(-500);
				m_pPlayer->SetDoubleJump(!m_pPlayer->GetDoubleJump());
			}*/
		}
		if (ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_RIGHT) && m_pPlayer->GetHorizontalVelocity() < 250)
		{
			m_pPlayer->SetHorizontalVelocity(m_pPlayer->GetHorizontalVelocity() + 250);
		}

		if (ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_LEFT) && m_pPlayer->GetHorizontalVelocity() > -250)
		{
			m_pPlayer->SetHorizontalVelocity(m_pPlayer->GetHorizontalVelocity() - 250);
		}
		
		if (!ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_RIGHT) && !ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_LEFT))
		{
			m_pPlayer->SetHorizontalVelocity(0);
		}

	}
	m_pPlayer->Process(deltaTime);

}

void
GameState::Draw(BackBuffer& backBuffer)
{
	m_pPlayer->Draw(backBuffer);
}
