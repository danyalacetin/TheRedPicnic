#ifndef __GAME_H__
#define __GAME_H__

// Local Includes:
#include "gameutils.h"

// Library Includes:
#include <vector>

// Forward Declarations
class BackBuffer;
class InputHandler;
class SoundManager;
class Sprite;
class AnimatedSprite;
class GameState;
class MenuState;
class GameMenuState;
class State;
class Background;
class FadeManager;

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

	State* GetPreviousState();
	void AddGameState();
	void AddGameMenuState();
	void DeleteState();
	void FadeTo(StateType state);
	Background* GetBackground();

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
	static float m_screenScaleRatio;

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

	// Fading Properites
	Fade m_fade;
	StateType m_fadeTo;
	float m_fadeOpacity;
	float m_fadeTime;

	float m_fTime = 0;
	float m_maxDuration = 4.0f;
	float m_holdDuration = 2.0f;

	// Game States:
	std::vector<State*> m_pGameStateStack;
	MenuState* m_pMenuState;
	GameState* m_pGameState;
	GameMenuState* m_pGameMenuState;
	
	// Background
	Background* m_pBackground;

private:

};

#endif // __GAME_H__
