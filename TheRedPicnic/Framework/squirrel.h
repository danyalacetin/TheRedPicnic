#ifndef __SQUIRREL_H__
#define __SQUIRREL_H__

// Forward Declarations:
#include "NonPlayableCharacter.h"


class Squirrel : public NonPlayableCharacter {
	//Member Methods:
public:
	Squirrel();

	void ProcessIdle(float deltaTime);
	void ProcessWalking(float deltaTime);
	void ProcessEating(float deltaTime);

	void Tracking(Entity& e);

protected:


private:

	//Member Data:
public:


protected:

private:

};


#endif //__SQUIRREL_H__