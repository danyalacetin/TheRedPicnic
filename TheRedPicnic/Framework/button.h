#ifndef __BUTTON_H__
#define __BUTTON_H__

// Superclass Includes:
#include "uielement.h"

// Local Includes:

// Library Includes:
#include <string>
#include <functional>

class BackBuffer;
class Sprite;
class Label;

class Button : public UiElement
{
public:
	//Member Methods:
	Button();
	~Button();
	bool Initialise(Sprite* sprite, std::string text);


	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	bool IsSelected();
	void SetSelected(bool selected);

	void OnPress();
	void SetOnPress(std::function<void()> fnOnPress);

	void SetPosition(Vector2f newPosition);
	void SetPosition(float fX, float fY);
	void SetPosition(int iX, int iY);

	void PositionChildren();

protected:

private:

	//Member Data:
public:

protected:

private:
	Sprite* m_pSprite;
	Label* m_pLabel;
	std::string m_text;
	bool m_selected;

	std::function<void()> m_fnOnPress;

};

#endif // __BUTTON_H__


