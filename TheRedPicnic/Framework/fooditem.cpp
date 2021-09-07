// This include:
#include "fooditem.h"

// Local includes:
#include "game.h"
#include "sprite.h"
#include "backbuffer.h"

// Library includes:
#include <cassert>

FoodItem::FoodItem()
	: Entity()
{

}

FoodItem::~FoodItem()
{

}

/*
bool
FoodItem::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;
	m_width = sprite->GetWidth() * Game::m_screenScaleRatio;
	m_height = sprite->GetHeight() * Game::m_screenScaleRatio;

	return (true);
}
*/

/*void
FoodItem::Draw(BackBuffer& backBuffer)
{
	m_pSprite->Draw(backBuffer);
}*/

/*void
FoodItem::Process()
{

}*/