#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

// Superclass Includes:
#include "state.h"

// Library includes:
#include <stack> 

class BackBuffer;
class PlayableCharacter;
class NonPlayableCharacter;
class Camera;

class GameState : public State
{
public:

	//Member Methods:
	GameState();
	~GameState();

	bool Initialise();
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

protected:

private:

	//Member Data:
public:
	static int m_ground;
	static float m_gravity;
	static float m_playerBoundaryMin;
	static float m_playerBoundaryMax;

protected:
	PlayableCharacter* m_pPlayer;
	NonPlayableCharacter* m_pEnemy;
	NonPlayableCharacter* m_pEnemy2;

private:

};

#endif // __GAMESTATE_H__


