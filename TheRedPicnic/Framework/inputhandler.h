// COMP710 GP 2D Framework 2019
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

protected:

private:
	InputHandler(const InputHandler& inputHandler);
	InputHandler& operator=(const InputHandler& inputHandler);

	void SetKeyPressed(SDL_Event event, bool status);

	//Member Data:
public:

protected:
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
