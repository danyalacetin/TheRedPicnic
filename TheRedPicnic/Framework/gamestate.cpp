// This include:
#include "gamestate.h"

// Local includes:
#include "game.h"
#include "state.h"
#include "resourcemanager.h"
#include "inputhandler.h"

// Library includes:
#include <cassert>

GameState::GameState()
	: State()
{
}

GameState::~GameState()
{
}

bool
GameState::Initialise()
{
	SetInputWait(50);
	return (true);
}

void
GameState::Process(float deltaTime)
{
	ProcessInputWait();

	if (ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_ESCAPE) && GetInputWait() == 0)
	{
		Game::GetInstance().AddGameMenuState();
	}
}

void
GameState::Draw(BackBuffer& backBuffer)
{
}
