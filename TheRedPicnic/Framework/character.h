#ifndef __ANIMATEDENTITY_H__
#define __ANIMATEDENTITY_H__

// Forward Declarations:
#include "entity.h"
class AnimatedSprite;

class Character : public Entity {
	//Member Methods:
public:
	Character();
	~Character();

	bool Initialise(Sprite* sprite);
	void Draw(BackBuffer& backBuffer);
	void ProcessFlip();

protected:

private:

	//Member Data:
public:


protected:
	AnimatedSprite* m_pSprite;

private:

};


#endif //__ANIMATEDENTITY_H__