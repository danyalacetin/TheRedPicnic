#ifndef __GAMEMENUSTATE_H__
#define __GAMEMENUSTATE_H__

// Superclass Includes:
#include "state.h"
#include "sprite.h"
#include "menu.h"
#include "image.h"
#include "label.h"

// Library includes:
#include <stack> 

class BackBuffer;

class GameMenuState : public State
{
public:

	//Member Methods:
	GameMenuState();
	~GameMenuState();

	bool Initialise(Sprite* pButton);
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void CreateGameMenu();

	void UpButtonPressed();
	void DownButtonPressed();
	void EnterButtonPressed();
	void EscapeButtonPressed();

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
	Menu* m_pGameMenu;
	Menu* m_pOptionsMenu;
	std::stack<Menu*> m_menuStack;

};

#endif // __INGAMEMENUSTATE_H__


