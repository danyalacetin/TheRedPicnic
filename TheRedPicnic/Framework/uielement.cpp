// This include:
#include "uielement.h"

// Local includes:
#include "game.h"

// Library includes:

UiElement::UiElement()
{
}

UiElement::~UiElement()
{
}

void UiElement::SetPosition(Vector2f newPosition)
{
	m_position = newPosition;
	PositionChildren();
}

void UiElement::SetPosition(float fX, float fY)
{
	SetPosition(Vector2f(fX, fY));
}

void UiElement::SetPosition(int iX, int iY)
{
	float fX = static_cast<float>(iX * Game::m_screenScaleRatio / 6);
	float fY = static_cast<float>(iY * Game::m_screenScaleRatio / 6);

	SetPosition(fX, fY);
}

void UiElement::SetDimensions(Vector2f newDimensions)
{
	m_dimensions.x = newDimensions.x * Game::m_screenScaleRatio / 6;
	m_dimensions.y = newDimensions.y * Game::m_screenScaleRatio / 6;
}

Vector2f UiElement::GetDimensions()
{
	return m_dimensions;
}

Vector2f UiElement::GetPosition()
{
	return m_position;
}
