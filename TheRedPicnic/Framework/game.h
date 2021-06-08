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
class Background;

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
	static Vector2f m_screenDimensions;

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
	
	// Background
	Background* m_pBackground;

	//-----Sprites-----

	// Main Menu
	Sprite* m_pTitleScreenSprite;
	Sprite* m_pButtonSprite;

	// Splash Screen
	Sprite* m_pFmodSprite;

	// Background
	Sprite* m_pBackgroundSprite;
	Sprite* m_pMidGroundSprite;
	Sprite* m_pGroundSprite;

	// Characters
	Sprite* m_pPlayerSprite;
	Sprite* m_pBunnySprite;
	Sprite* m_pSquirrelSprite;

	// Objects
	Sprite* m_pAppleSprite;
	Sprite* m_pChickenSprite;
	Sprite* m_pMuffinSprite;
	Sprite* m_pPieSprite;

private:

};

#endif // __GAME_H__
