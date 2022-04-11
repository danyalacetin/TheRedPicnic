#ifndef __BUNNY_H__
#define __BUNNY_H__

// Forward Declarations:
#include "NonPlayableCharacter.h"


class Bunny : public NonPlayableCharacter {
	//Member Methods:
public:
	Bunny();

	void ProcessAnimation(float deltaTime);

	void ProcessIdle(float deltaTime);
	void ProcessWalking(float deltaTime);
	void ProcessEating(float deltaTime);

	void Tracking(Entity& e);
	void FoodReached(FoodItem& food);

protected:


private:

	//Member Data:
public:


protected:

private:

};


#endif //__BUNNY_H__