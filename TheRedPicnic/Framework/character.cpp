// This include:
#include "character.h"

// Local includes:
#include "sprite.h"
#include "animatedsprite.h"
#include "backbuffer.h"

// Library includes:
#include <cassert>

Character::Character()
	: Entity()
	, m_pSprite(0)
{

}

Character::~Character()
{
	delete m_pSprite;
	m_pSprite = 0;
}

bool
Character::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = new AnimatedSprite();
	m_pSprite->Initialise(sprite);

	m_pSprite->SetFrameX(0);
	m_pSprite->SetFrameY(0);

	m_pSprite->SetLooping(true);

	m_width = m_pSprite->GetWidth();
	m_height = m_pSprite->GetHeight();

	return (true);
}

void
Character::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->GetSprite()->SetX(static_cast<int>(m_x));
	m_pSprite->GetSprite()->SetY(static_cast<int>(m_y));

	if (!m_hidden)
	{
		m_pSprite->Draw(backBuffer);
	}
}

void
Character::ProcessFlip()
{
	if (m_velocityX > 0)
	{	//Don't Flip Sprite
		m_pSprite->SetFlipped(false);
	}
	else if (m_velocityX < 0)
	{	//Flip Sprite
		m_pSprite->SetFlipped(true);
	}
}