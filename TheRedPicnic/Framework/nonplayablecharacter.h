#ifndef __NONPLAYABLECHARACTER_H__
#define __NONPLAYABLECHARACTER_H__

// Forward Declarations:
#include "Character.h"
#include "gameutils.h"
class AnimatedSprite;

class NonPlayableCharacter : public Character {
	//Member Methods:
public:
	NonPlayableCharacter();

	void Process(float deltaTime);

	virtual void ProcessIdle(float deltaTime);
	virtual void ProcessWalking(float deltaTime);
	virtual void ProcessRunning(float deltaTime);
	virtual void ProcessEating(float deltaTime);

	virtual void Tracking(Entity& e);

	void SetState(NpcState state);
	NpcState GetState();

protected:


private:

	//Member Data:
public:


protected:
	float m_animationWait;
	NpcState m_state;

private:

};


#endif //__NONPLAYABLECHARACTER_H__