#ifndef __STATE_H__
#define __STATE_H__

#include "gameutils.h"
class BackBuffer;

class State
{
public:
	//Member Methods:
	State();
	virtual ~State() = 0;

	virtual bool Initialise();
	virtual void Process(float deltaTime);
	virtual void Draw(BackBuffer& backBuffer);

	virtual StateType GetStateType();

protected:

private:

	//Member Data:
public:

protected:
	StateType m_type;

private:
	int m_inputwait;

};

#endif // __STATE_H__


