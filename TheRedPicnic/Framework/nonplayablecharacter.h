#ifndef __NONPLAYABLECHARACTER_H__
#define __NONPLAYABLECHARACTER_H__

// Forward Declarations:
#include "Character.h"
class AnimatedSprite;

class NonPlayableCharacter : public Character {
	//Member Methods:
public:
	NonPlayableCharacter();

	void Process(float deltaTime);
	void ProcessAnimation(float deltaTime);
	void Tracking(Entity& e);

protected:


private:

	//Member Data:
public:


protected:
	float m_animationWait;

private:

};


#endif //__NONPLAYABLECHARACTER_H__