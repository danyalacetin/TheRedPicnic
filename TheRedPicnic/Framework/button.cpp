// This include:
#include "button.h"

// Local includes:
#include "sprite.h"
#include "game.h"
#include "label.h"
//#include "../soundmanager.h"

// Library includes:
#include <cassert>

Button::Button()
	: m_selected(false)
	, m_fnOnPress([] {})
{
}


Button::~Button()
{
	delete m_pLabel;
}

bool
Button::Initialise(Sprite* sprite, std::string text)
{
	m_pSprite = sprite;
	m_text = text;

	SetDimensions(sprite->GetDimensionsf());

	m_pLabel = new Label();
	m_pLabel->Initialise(text);
	m_pLabel->SetAlignment(ALIGN_CENTRE);
	m_pLabel->SetColour(0x00, 0x00, 0x00);

	return (true);
}

void
Button::Process(float deltaTime)
{
	if (m_selected)
	{
		m_pLabel->SetColour(0xFF, 0x00, 0x00);
	}
	else
	{
		m_pLabel->SetColour(0x00, 0x00, 0x00);
	}
}

void
Button::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<int>(m_position.x));
	m_pSprite->SetY(static_cast<int>(m_position.y));
	m_pSprite->Draw(backBuffer);
	m_pLabel->Draw(backBuffer);
}

void
Button::OnPress()
{
	//SoundManager::GetInstance().PlaySound(BUTTONPRESS);
	m_fnOnPress();
}

void
Button::SetOnPress(std::function<void()> fnOnPress)
{
	m_fnOnPress = fnOnPress;
}

bool
Button::IsSelected()
{
	return m_selected;
}

void
Button::SetSelected(bool selected)
{
	m_selected = selected;
	if (selected)
	{
		m_pLabel->SetColour(0xFF, 0x00, 0x00);
	}
	else
	{
		m_pLabel->SetColour(0x00, 0x00, 0x00);
	}

}

void
Button::SetPosition(Vector2f newPosition)
{
	UiElement::SetPosition(newPosition);
}

void
Button::SetPosition(float fX, float fY)
{
	SetPosition(Vector2f(fX, fY));
}

void
Button::SetPosition(int iX, int iY)
{
	float fX = static_cast<float>(iX);
	float fY = static_cast<float>(iY);

	SetPosition(fX, fY);
}

void Button::PositionChildren()
{
	m_pLabel->SetPosition(m_position.x, m_position.y + 3);
}

