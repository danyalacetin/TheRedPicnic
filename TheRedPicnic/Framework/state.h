#ifndef __STATE_H__
#define __STATE_H__


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
	virtual void ProcessInputWait();

	virtual int GetInputWait();
	virtual void SetInputWait(int i);

protected:

private:

	//Member Data:
public:

protected:

private:
	int m_inputwait;

};

#endif // __STATE_H__


