#ifndef __MENUSTATE_H__
#define __MENUSTATE_H__

// Superclass Includes:
#include "state.h"

// Library includes:
#include <stack> 

class BackBuffer;
class Sprite;
class Menu;
class Image;
class Button;
class Label;

class MenuState : public State
{
public:

	//Member Methods:
	MenuState();
	~MenuState();

	bool Initialise(Sprite* pButton, Sprite* pTitleScreen);
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void CreateMainMenu();
	void CreateOptionsMenu();
	void CreateCreditsMenu();

	void MenuReturn();

	void UpButtonPressed();
	void DownButtonPressed();
	void EnterButtonPressed();

	std::stack<Menu*> GetMenuStack();

protected:

private:

	//Member Data:
public:

protected:

private:

	//GUI ELEMENTS
	Button* m_pButton;
	Image* m_pImage;
	Label* m_pLabel;

	//SPRITES
	Sprite* m_pButtonSprite;
	Sprite* m_pTitleScreen;

	//MENUS
	Menu* m_pMainMenu;
	Menu* m_pOptionsMenu;
	Menu* m_pCreditsMenu;
	std::stack<Menu*> m_menuStack;

};

#endif // __MENUSTATE_H__


