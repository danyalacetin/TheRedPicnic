#ifndef __NONPLAYABLECHARACTER_H__
#define __NONPLAYABLECHARACTER_H__

// Forward Declarations:
#include "Character.h"
#include "gameutils.h"
#include "fooditem.h"
class AnimatedSprite;
class FoodItem;
class GameState;

class NonPlayableCharacter : public Character {
	//Member Methods:
public:
	NonPlayableCharacter();

	void Process(float deltaTime);
	void ProcessCollisionDetection(float deltaTime);
	virtual void ProcessAnimation(float deltaTime);

	virtual void ProcessIdle(float deltaTime);
	virtual void ProcessWalking(float deltaTime);
	virtual void ProcessRunning(float deltaTime);
	virtual void ProcessEating(float deltaTime);

	virtual void Tracking(Entity& e);
	virtual void FoodReached(FoodItem& food);

	void SetState(NpcState state);
	NpcState GetState();

protected:


private:

	//Member Data:
public:


protected:
	float m_animationWait;
	float m_animationWaitDuration;
	NpcState m_state;
	FoodItem* m_food;

private:

};


#endif //__NONPLAYABLECHARACTER_H__