// COMP710 GP 2D Framework 2019

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"
#include "logmanager.h"

// Library includes:
#include <cassert>

//
#include <iostream>

InputHandler::InputHandler()
: m_pGameController(0)
{

}

InputHandler::~InputHandler()
{
	if (m_pGameController)
	{
		SDL_JoystickClose(m_pGameController);
		m_pGameController = 0;
	}
}

bool 
InputHandler::Initialise()
{

	return (true);
}

void 
InputHandler::ProcessInput(Game& game)
{
	//Receive Input Events
	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		//Debug purpose quit
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			game.Quit();
		}
		//------------------

		//Checks type of event (Key down, Key Up or Quit)
		switch (event.type)
		{
		case SDL_QUIT:
			game.Quit();
			break;

		case SDL_KEYDOWN:
			SetKeyPressed(event, true);
			break;

		case SDL_KEYUP:
			SetKeyPressed(event, false);
			break;

		default:
			break;
		}
	}
}

void
InputHandler::SetKeyPressed(SDL_Event event, bool status)
{
	LogManager::GetInstance().Log(SDL_GetKeyName(event.key.keysym.sym));

	switch (event.key.keysym.sym)
	{
	case SDLK_UP:
		m_KeyUp = status;
		break;

	case SDLK_DOWN:
		m_KeyDown = status;
		break;

	case SDLK_LEFT:
		m_KeyLeft = status;
		break;

	case SDLK_RIGHT:
		m_KeyRight = status;
		break;

	case SDLK_ESCAPE:
		m_KeyEsc = status;
		break;

	case SDLK_RETURN:
		m_KeyEnter = status;
		break;

	default:
		break;
	}
}

bool
InputHandler::GetKeyPressed(int i)
{
	switch (i)
	{
	case SDLK_UP:
		return m_KeyUp;

	case SDLK_DOWN:
		return m_KeyDown;

	case SDLK_LEFT:
		return m_KeyLeft;

	case SDLK_RIGHT:
		return m_KeyRight;

	case SDLK_ESCAPE:
		return m_KeyEsc;

	case SDLK_RETURN:
		return m_KeyEnter;

	default:
		return false;
	}
}
