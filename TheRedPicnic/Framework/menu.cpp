// COMP710 GP 2D Framework 2019

// This include:
#include "menu.h"

// Local includes:
#include "sprite.h"
#include "game.h"
#include "button.h"
#include "uielement.h"
//#include "../soundmanager.h"

// Library includes:
#include <cassert>

Menu::Menu()
	: m_iSelectedButton(0)
	, m_SelectionCooldown(0)
{

}

Menu::~Menu()
{
	for (UiElement* m_uiElement : m_uiElementContainor)
	{
		delete m_uiElement;
	}

	m_uiElementContainor.clear();
	m_buttonContainer.clear();
}

bool
Menu::Initialise()
{
	m_SelectionCooldown = 50;
	return (true);
}

void
Menu::Process(float deltaTime)
{
	if (m_SelectionCooldown != 0)
	{
		m_SelectionCooldown--;
	}
	m_buttonContainer[m_iSelectedButton]->Process(deltaTime);
}

void
Menu::Draw(BackBuffer& backBuffer)
{
	for (UiElement* m_uiElement : m_uiElementContainor)
	{
		m_uiElement->Draw(backBuffer);
	}
}

void
Menu::AddChild(UiElement* uiElement)
{
	m_uiElementContainor.push_back(uiElement);
}

void
Menu::AddButton(Button* button)
{
	m_buttonContainer.push_back(button);
	AddChild(button);
}

std::vector<Button*>&
Menu::GetButtonContainor()
{
	return m_buttonContainer;
}

int
Menu::IncrementSelected()
{
	if (m_iSelectedButton < m_buttonContainer.size() - 1)
	{
		m_iSelectedButton++;
		m_SelectionCooldown = 50;
		//SoundManager::GetInstance().PlaySound(BUTTONSELECT);
	}

	return m_iSelectedButton;
}

int
Menu::DecrementSelected()
{
	if (m_iSelectedButton > 0)
	{
		m_iSelectedButton--;
		m_SelectionCooldown = 50;
		//SoundManager::GetInstance().PlaySound(BUTTONSELECT);
	}

	return m_iSelectedButton;
}

int Menu::GetSelected() const
{
	return m_iSelectedButton;
}

Button& Menu::GetSelectedButton() const
{
	return *m_buttonContainer[m_iSelectedButton];
}

int Menu::GetSelectionCooldown()
{
	return m_SelectionCooldown;
}

void Menu::SetSelectionCooldown(int cooldown)
{
	m_SelectionCooldown = cooldown;
}

void Menu::PositionElements(Vector2f containerDimensions)
{
	// calcluate / set spacing
	float fHSpacing = 50.0f;

	// calculate max height and width
	float fCurrentHeight = -fHSpacing;
	float fCurrentWidth = 0.0f;

	for each (UiElement * element in m_uiElementContainor)
	{
		Vector2f dimensions = element->GetDimensions();
		fCurrentHeight += fHSpacing + dimensions.y;

		if (fCurrentWidth < dimensions.x)
		{
			fCurrentWidth = dimensions.x;
		}
	}

	UiElement* pPrevElement = m_uiElementContainor[0];
	float fFirstElementHeight = pPrevElement->GetDimensions().y;

	float fStartX = containerDimensions.x / 2.0f;
	float fCurrY = (containerDimensions.y - fCurrentHeight + fFirstElementHeight) / 2.0f;

	pPrevElement->SetPosition(fStartX, fCurrY);

	for (size_t i = 1; i < m_uiElementContainor.size(); ++i)
	{
		UiElement* pCurrElement = m_uiElementContainor[i];

		float fPrevHeight = pPrevElement->GetDimensions().y;
		float fCurrHeight = pCurrElement->GetDimensions().y;

		float fChangeX = (fPrevHeight + fCurrHeight) / 2.0f + fHSpacing;

		fCurrY += fChangeX;

		pCurrElement->SetPosition(fStartX, fCurrY);
		pPrevElement = pCurrElement;
	}
}