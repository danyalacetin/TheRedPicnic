#ifndef __INPUTHANDER_H__
#define __INPUTHANDER_H__

// Library includes:
#include <SDL.h>

// Forward Declarations:
class Game;

class InputHandler
{
	//Member Methods:
public:
	InputHandler();
	~InputHandler();

	bool Initialise();
	void ProcessInput(Game& game);

	bool GetKeyPressed(int i);
	void SetKeyPressed(int i, bool status);

protected:

private:
	InputHandler(const InputHandler& inputHandler);
	InputHandler& operator=(const InputHandler& inputHandler);

	//Member Data:
public:

protected:
	static InputHandler* sm_pInstance;

	SDL_Joystick* m_pGameController;

	bool m_KeyUp;
	bool m_KeyDown;
	bool m_KeyRight;
	bool m_KeyLeft;

	bool m_KeyEnter;
	bool m_KeySpace;
	bool m_KeyEsc;

private:

};

#endif // __INPUTHANDER_H__
