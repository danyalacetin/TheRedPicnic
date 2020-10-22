// COMP710 GP 2D Framework 2019

// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <cstdio>

// Static Members:
Game* Game::sm_pInstance = 0;

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
, m_pInputHandler(0)
, m_looping(true)
, m_executionTime(0)
, m_elapsedSeconds(0)
, m_frameCount(0)
, m_FPS(0)
, m_numUpdates(0)
, m_lastTime(0)
, m_lag(0)
{
	
}

Game::~Game()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pInputHandler;
	m_pInputHandler = 0;

	//Delete Sprites
	delete m_pTest;
}

bool 
Game::Initialise()
{
	const int width = 1920;
	const int height = 1080;

	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(width, height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	m_lastTime = SDL_GetPerformanceCounter();
	m_lag = 0.0f;

	m_pBackBuffer->SetClearColour(0xCC, 0xCC, 0xCC);

	m_pTest = m_pBackBuffer->CreateSprite("assets/playership.png");

	//Create the player instance.

	//Intilise map.

	return (true);
}

bool 
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput(*this);
	
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

	// Update the game world simulation:

	m_pTest->Process(deltaTime);
	m_pInputHandler->GetKeyPressed(SDLK_UP);
	

	//Process each entity, partical and gui elements

	//Update player

	//Check collisions

	//Remove any dead entities or particals from the container
}

void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	m_pTest->Draw(backBuffer);

	//Draw all Entities, particals and gui elements
	
	backBuffer.Present();
}

void 
Game::Quit()
{
	m_looping = false;
}
