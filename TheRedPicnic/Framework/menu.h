// COMP710 GP 2D Framework 2019
#ifndef __MENU_H__
#define __MENU_H__

#include "gameutils.h"

#include <vector>

class BackBuffer;
class Sprite;
class UiElement;
class Button;

class Menu
{
public:
	//Member Methods:
	Menu();
	~Menu();

	bool Initialise();
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void AddChild(UiElement* uiElement);
	void AddButton(Button* button);
	std::vector<Button*>& GetButtonContainor();

	int IncrementSelected();
	int DecrementSelected();
	int GetSelected() const;
	Button& GetSelectedButton() const;

	int GetSelectionCooldown();
	void SetSelectionCooldown(int cooldown);

	void PositionElements(Vector2f containerDimensions);

protected:

private:

	//Member Data:
public:
	int m_SelectionCooldown;

protected:

private:

	unsigned m_iSelectedButton;

	std::vector<UiElement*> m_uiElementContainor;
	std::vector<Button*> m_buttonContainer;

};

#endif // __MENU_H__


