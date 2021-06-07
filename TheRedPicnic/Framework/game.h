// COMP710 GP 2D Framework 2019
#ifndef __GAME_H__
#define __GAME_H__

// Local Includes:
#include "gameutils.h"

// Library Includes:
#include <vector>

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class GameState;
class MenuState;
class GameMenuState;
class State;

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	bool Initialise();
	bool DoGameLoop();
	void Quit();

	bool LoadSprites();

	State* GetPreviousState();
	void AddGameState();
	void AddGameMenuState();
	void DeleteState();

protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:
	static Vector2f screenDimensions;

protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	bool m_looping;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	__int64 m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;

	// Game States:
	std::vector<State*> m_pGameStateStack;
	MenuState* m_pMenuState;
	GameState* m_pGameState;
	GameMenuState* m_pGameMenuState;
	
	//-----Sprites-----

	// Main Menu
	Sprite* m_pTitleScreen;
	Sprite* m_pButton;

	// Splash Screen
	Sprite* m_pFmod;

	// Background
	Sprite* m_pBackground;
	Sprite* m_pMidGround;
	Sprite* m_pGround;

	// Characters
	Sprite* m_pPlayer;
	Sprite* m_pBunny;
	Sprite* m_pSquirrel;

	// Objects
	Sprite* m_pApple;
	Sprite* m_pChicken;
	Sprite* m_pMuffin;
	Sprite* m_pPie;

private:

};

#endif // __GAME_H__
