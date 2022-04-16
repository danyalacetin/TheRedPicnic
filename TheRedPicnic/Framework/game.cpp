// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "resourcemanager.h"
#include "spritemanager.h"
#include "sprite.h"
#include "animatedsprite.h"
#include "menustate.h"
#include "gamestate.h"
#include "gamemenustate.h"
#include "background.h"
#include "soundmanager.h"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <cstdio>
#include <Windows.h>

// Static Members:
Game* Game::sm_pInstance = 0;
Vector2f Game::m_screenDimensions = Vector2f();
float Game::m_screenScaleRatio = 0;

Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{ 
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void 
Game::DestroyInstance()
{
	delete sm_pInstance; 
	sm_pInstance = 0;
}

Game::Game()
: m_pBackBuffer(0)
, m_looping(true)
, m_executionTime(0)
, m_elapsedSeconds(0)
, m_frameCount(0)
, m_FPS(0)
, m_numUpdates(0)
, m_lastTime(0)
, m_lag(0)
, m_pGameState(0)
{
	
}

Game::~Game()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pBackground;
	m_pBackground = 0;

	//----Delete-all-game-states----
	while (!m_pGameStateStack.empty())
	{
		delete m_pGameStateStack.back();
		m_pGameStateStack.pop_back();
	}

	ResourceManager::DestroyInstance();
	SoundManager::DestroyInstance();
}

bool 
Game::Initialise()
{
	HWND hd = GetDesktopWindow();
	RECT rect;
	GetClientRect(hd, &rect);
	const int width = (rect.right - rect.left);
	const int height = (rect.bottom - rect.top);

	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(width, height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	if (!ResourceManager::Setup(m_pBackBuffer->GetRenderer()))
	{
		LogManager::GetInstance().Log("ResourceManager Setup Failed");
		return (false);
	}

	m_lastTime = SDL_GetPerformanceCounter();
	m_lag = 0.0f;

	m_pBackBuffer->SetClearColour(0xCC, 0xCC, 0xFF);

	m_screenDimensions.x = static_cast<float>(width);
	m_screenDimensions.y = static_cast<float>(height);

	//screen height / background sprite height = ratio
	m_screenScaleRatio = m_screenDimensions.y / 240;

	ResourceManager::GetInstance().GetSpriteManager().LoadSprites(*m_pBackBuffer);

	m_pBackground = new Background();
	m_pBackground->Initialise(ResourceManager::GetInstance().GetSpriteManager().GetSprite(BACKGROUND),
							  ResourceManager::GetInstance().GetSpriteManager().GetSprite(MIDGROUND), 
							  ResourceManager::GetInstance().GetSpriteManager().GetSprite(GROUND));

	m_pMenuState = new MenuState();
	m_pMenuState->Initialise(ResourceManager::GetInstance().GetSpriteManager().GetSprite(BUTTON),
							 ResourceManager::GetInstance().GetSpriteManager().GetSprite(TITLE));

	m_pGameStateStack.push_back(m_pMenuState);

	m_fadeOut = false;
	m_fadeIn = true;
	m_fadeTo = MainMenu;
	m_fadeOpacity = 255; //full black

	return (true);
}

bool 
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;
	
	ResourceManager::GetInstance().GetInputHandler().ProcessInput(*this);

	if (m_looping)
	{
		Uint64 current = SDL_GetPerformanceCounter();

		float deltaTime = (current - m_lastTime) / static_cast<float>(SDL_GetPerformanceFrequency());
		
		m_lastTime = current;

		m_executionTime += deltaTime;

		Process(deltaTime);
	
		m_lag += deltaTime;

		int innerLag = 0;

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
			++innerLag;
		}

		// DEBUG STUB:
//		char buffer[64];
//		sprintf(buffer, "%f", deltaTime);
//		LogManager::GetInstance().Log(buffer);

		Draw(*m_pBackBuffer);
	}

	return (m_looping);
}

void
Game::Process(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	if (m_fadeIn)
	{
		m_fadeOpacity -= 5;

		if (m_fadeOpacity <= 0)
		{
			m_fadeIn = false;
			m_fadeOpacity = 0;
		}
	}

	if (m_fadeOut)
	{
		m_fadeOpacity += 5;

		if (m_fadeOpacity >= 255)
		{

			m_fadeOut = false;
			m_fadeIn = true;
			m_fadeOpacity = 255;

			switch (m_fadeTo)
			{
			case MainMenu:
				DeleteState();
				DeleteState();
				break;
			case InGame:
				AddGameState();
				break;
			}
		}
	}
	else
	{
		// Plays Sound:
		SoundManager::GetInstance().Update();

		// Update the game world simulation:
		m_pGameStateStack.back()->Process(deltaTime);
	}
}

void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	m_pBackground->Draw(backBuffer);	//Draw Background always.

	if (m_pGameStateStack.back()->GetStateType() == InGameMenu)		//If in game menu state, draw the paused game aswell.
	{
		m_pGameState->Draw(backBuffer);
	}

	m_pGameStateStack.back()->Draw(backBuffer);						//Draws current state.

	backBuffer.SetDrawColour(0,0,0, m_fadeOpacity);
	backBuffer.DrawRectangle(0, 0, m_screenDimensions.x, m_screenDimensions.y);
	backBuffer.Present();
}

void 
Game::Quit()
{
	m_looping = false;
}

State*
Game::GetPreviousState()
{
	return m_pGameStateStack[m_pGameStateStack.size() - 2];
}

void
Game::AddGameState()
{
	m_pGameState = new GameState();
	m_pGameState->Initialise();
	m_pGameStateStack.push_back(m_pGameState);
}

void
Game::AddGameMenuState()
{
	m_pGameMenuState = new GameMenuState();
	m_pGameMenuState->Initialise(ResourceManager::GetInstance().GetSpriteManager().GetSprite(BUTTON));
	m_pGameStateStack.push_back(m_pGameMenuState);
}

void
Game::DeleteState()
{
	delete m_pGameStateStack.back();
	m_pGameStateStack.pop_back();
}

void
Game::FadeTo(StateType state)
{
	m_fadeTo = state;
	m_fadeOut = true;
}

Background*
Game::GetBackground()
{
	return m_pBackground;
}
