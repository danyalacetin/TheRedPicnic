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
#include "fooditem.h"
#include "entity.h"
#include "bunny.h"
#include "squirrel.h"
#include "raccoon.h"

// Library includes:
#include <cassert>

//static members:
int GameState::m_ground = 0;
float GameState::m_gravity = 0;
float GameState::m_playerBoundaryMin = 0;
float GameState::m_playerBoundaryMax = 0;

PlayableCharacter* GameState::m_pPlayer = 0;
std::vector<NonPlayableCharacter*> GameState::m_pEnemyContainer;
std::vector<FoodItem*> GameState::m_pFoodItemContainer;

GameState::GameState()
	: State()
{
}

GameState::~GameState()
{
	delete m_pPlayer;
	m_pPlayer = nullptr;

	for (NonPlayableCharacter* pEnemy : m_pEnemyContainer) {
		delete pEnemy;
		pEnemy = nullptr;
	}

	for (FoodItem* pFood : m_pFoodItemContainer) {
		delete pFood;
		pFood = nullptr;
	}

	Camera::DestroyInstance();
}

bool
GameState::Initialise()
{
	m_type = InGame;

	//Initilise game variables
	m_gravity = 650;
	m_ground = 190 * Game::m_screenScaleRatio;
	m_playerBoundaryMax = 160 * Game::m_screenScaleRatio;
	m_playerBoundaryMin = 60 * Game::m_screenScaleRatio;

	//Create Camera
	Camera::CreateInstance();

	//Create and initilise player
	m_pPlayer = new PlayableCharacter();
	m_pPlayer->Initialise(ResourceManager::GetInstance().GetSpriteManager().GetSprite(PLAYER));
	m_pPlayer->SetPosition(30 * Game::m_screenScaleRatio, m_ground);

	//Create and initilise npcs
	for (int i = 0;i < 2;i++)
	{
		Squirrel* pEnemy = new Squirrel();
		pEnemy->Initialise(ResourceManager::GetInstance().GetSpriteManager().GetSprite(SQUIRREL));
		pEnemy->SetPosition(140 * m_pEnemyContainer.size() * Game::m_screenScaleRatio, m_ground - (i*50));
		m_pEnemyContainer.push_back(pEnemy);
	}

	for (int i = 0; i < 2; i++)
	{
		Bunny* pEnemy = new Bunny();
		pEnemy->Initialise(ResourceManager::GetInstance().GetSpriteManager().GetSprite(BUNNY));
		pEnemy->SetPosition(140 * m_pEnemyContainer.size() * Game::m_screenScaleRatio, m_ground - (i * 50));
		m_pEnemyContainer.push_back(pEnemy);
	}

	for (int i = 0; i < 1; i++)
	{
		Raccoon* pEnemy = new Raccoon();
		pEnemy->Initialise(ResourceManager::GetInstance().GetSpriteManager().GetSprite(RACCOON));
		pEnemy->SetPosition(140 * m_pEnemyContainer.size() * Game::m_screenScaleRatio, m_ground - (i * 50));
		m_pEnemyContainer.push_back(pEnemy);
	}

	return (true);
}

void
GameState::Process(float deltaTime)
{
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-PLAYER-=-INPUT-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	//If Esc key pressed
	if (ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_ESCAPE))
	{
		ResourceManager::GetInstance().GetInputHandler().SetKeyPressed(SDLK_ESCAPE, false);
		Game::GetInstance().AddGameMenuState();
	}

	//If Player is not being pushed (Able to recieve input)
	if (!m_pPlayer->IsPushed())
	{
		//If Up key pressed
		if (ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_UP))
		{
			//Jump if able
			if (m_pPlayer->IsGrounded() || m_pPlayer->GetDoubleJump())
			{
				m_pPlayer->SetVerticalVelocity(-m_pPlayer->GetMaxVerticalVelocity());
				m_pPlayer->SetDoubleJump(!m_pPlayer->GetDoubleJump());
				ResourceManager::GetInstance().GetInputHandler().SetKeyPressed(SDLK_UP, false);
			}
		}

		//If Right key pressed
		if (ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_RIGHT) && m_pPlayer->GetHorizontalVelocity() < m_pPlayer->GetMaxHorizontalVelocity())
		{
			m_pPlayer->SetHorizontalVelocity(m_pPlayer->GetHorizontalVelocity() + m_pPlayer->GetMaxHorizontalVelocity());
		}

		//If Left key pressed
		if (ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_LEFT) && m_pPlayer->GetHorizontalVelocity() > -m_pPlayer->GetMaxHorizontalVelocity())
		{
			m_pPlayer->SetHorizontalVelocity(m_pPlayer->GetHorizontalVelocity() - m_pPlayer->GetMaxHorizontalVelocity());
		}

		//If Right and Left key pressed
		if (!ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_RIGHT) && !ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_LEFT))
		{
			m_pPlayer->SetHorizontalVelocity(0);
		}
	}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


	//Proccess Background
	Game::GetInstance().GetBackground()->Process(deltaTime);

	//Proccess Player
	m_pPlayer->Process(deltaTime);

	//Process all fooditems (Movment and player collision)
	for (FoodItem* pFood : m_pFoodItemContainer)
	{
		pFood->ProcessMovement(deltaTime);
	}

	//Process all enemies (Movment, Tracking and Collision)
	for (NonPlayableCharacter* pEnemy : m_pEnemyContainer) 
	{
		pEnemy->Process(deltaTime);
	}
}

void
GameState::Draw(BackBuffer& backBuffer)
{
	//Draws Player
	m_pPlayer->Draw(backBuffer);

	//Draws all Enemies
	for (NonPlayableCharacter* pEnemy : m_pEnemyContainer) 
	{
		pEnemy->Draw(backBuffer);
	}

	//Draws all dropped food items
	for (FoodItem* pFood : m_pFoodItemContainer)
	{
		pFood->Draw(backBuffer);
	}
}
