#ifndef __PLAYER_H__
#define __PLAYER_H__

// Forward Declarations:
#include "Character.h"
class AnimatedSprite;

class PlayableCharacter : public Character {
	//Member Methods:
public:
	PlayableCharacter();

	void Process(float deltaTime);
	void ProcessAnimation(float deltaTime);
	void ProcessPlayerBoundryChecks(float deltaTime);
	void SetDoubleJump(bool b);
	bool GetDoubleJump();

protected:


private:

	//Member Data:
public:


protected:
	bool m_canDoubleJump;
	bool m_damageWait;

private:

};


#endif //__PLAYER_H__