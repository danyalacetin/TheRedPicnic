#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

// Superclass Includes:
#include "state.h"

// Library includes:
#include <stack> 

class BackBuffer;
class PlayableCharacter;

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

protected:
	PlayableCharacter* m_pPlayer;

private:

};

#endif // __GAMESTATE_H__


