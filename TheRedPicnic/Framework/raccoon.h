#ifndef __RACCOON_H__
#define __RACCOON_H__

// Forward Declarations:
#include "NonPlayableCharacter.h"


class Raccoon : public NonPlayableCharacter {
	//Member Methods:
public:
	Raccoon();
	void ProcessIdle(float deltaTime);
	void ProcessWalking(float deltaTime);
	void ProcessRunning(float deltaTime);
	void Tracking(Entity& e);

protected:


private:

	//Member Data:
public:


protected:

private:

};


#endif //__BUNNY_H__