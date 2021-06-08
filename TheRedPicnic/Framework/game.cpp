// COMP710 GP 2D Framework 2019

// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "resourcemanager.h"
#include "sprite.h"
#include "animatedsprite.h"
#include "menustate.h"
#include "gamestate.h"
#include "gamemenustate.h"
#include "background.h"

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


	//----Delete-Sprites----

	// Main Menu
	delete m_pTitleScreenSprite;
	m_pTitleScreenSprite = 0;
	delete m_pButtonSprite;
	m_pButtonSprite = 0;

	// Splash Screen
	delete m_pFmodSprite;

	// Background
	delete m_pBackgroundSprite;
	delete m_pMidGroundSprite;
	delete m_pGroundSprite;

	// Characters
	delete m_pPlayerSprite;
	delete m_pBunnySprite;
	delete m_pSquirrelSprite;

	// Objects
	delete m_pAppleSprite;
	delete m_pChickenSprite;
	delete m_pMuffinSprite;
	delete m_pPieSprite;

	ResourceManager::DestroyInstance();
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

	m_pBackBuffer->SetClearColour(0xCC, 0xCC, 0xCC);

	m_screenDimensions.x = static_cast<float>(width);
	m_screenDimensions.y = static_cast<float>(height);

	//screen height / background sprite height = ratio
	m_screenScaleRatio = m_screenDimensions.y / 240;

	LoadSprites();

	m_pBackground = new Background();
	m_pBackground->Initialise(m_pBackgroundSprite, m_pMidGroundSprite, m_pGroundSprite);

	m_pMenuState = new MenuState();
	m_pMenuState->Initialise(m_pButtonSprite, m_pTitleScreenSprite);
	m_pGameStateStack.push_back(m_pMenuState);

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

	// Update the game world simulation:
	m_pGameStateStack.back()->Process(deltaTime);
}

void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	m_pBackground->Draw(backBuffer);
	m_pGameStateStack.back()->Draw(backBuffer);
	
	backBuffer.Present();
}

void 
Game::Quit()
{
	m_looping = false;
}

bool Game::LoadSprites()
{
	// Main Menu
	m_pTitleScreenSprite = m_pBackBuffer->CreateSprite("assets/Title.png");
	m_pButtonSprite = m_pBackBuffer->CreateSprite("assets/Button.png");

	// Splash Screen
	m_pFmodSprite = m_pBackBuffer->CreateSprite("assets/Sound.png");

	// Background
	m_pBackgroundSprite = m_pBackBuffer->CreateSprite("assets/Background.png");
	m_pMidGroundSprite = m_pBackBuffer->CreateSprite("assets/Midground.png");
	m_pGroundSprite = m_pBackBuffer->CreateSprite("assets/Ground.png");

	// Characters
	m_pPlayerSprite = m_pBackBuffer->CreateSprite("assets/PlayerSpriteSheet.png");
	m_pBunnySprite = m_pBackBuffer->CreateSprite("assets/Bunny.png");
	m_pSquirrelSprite = m_pBackBuffer->CreateSprite("assets/Squirrel.png");

	// Objects
	m_pAppleSprite = m_pBackBuffer->CreateSprite("assets/FoodSpriteApple.png");
	m_pChickenSprite = m_pBackBuffer->CreateSprite("assets/FoodSpriteChicken.png");
	m_pMuffinSprite = m_pBackBuffer->CreateSprite("assets/FoodSpriteMuffin.png");
	m_pPieSprite = m_pBackBuffer->CreateSprite("assets/FoodSpritePieSlice.png");

	return true;
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
	m_pGameMenuState->Initialise(m_pButtonSprite);
	m_pGameStateStack.push_back(m_pGameMenuState);
}

void
Game::DeleteState()
{
	delete m_pGameStateStack.back();
	m_pGameStateStack.pop_back();
	m_pGameStateStack.back()->SetInputWait(50);
}
