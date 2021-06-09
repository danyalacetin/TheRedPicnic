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

	bool GetDoubleJump();
	void SetDoubleJump(bool b);
	int GetBorderMin();
	int GetBorderMax();

protected:


private:

	//Member Data:
public:


protected:
	int m_borderMin;
	int m_borderMax;
	bool m_doubleJump;

private:

};


#endif //__PLAYER_H__