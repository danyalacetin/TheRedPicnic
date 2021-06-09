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

	//SetWidth(m_pSprite->GetFrameWidth() * m_pSprite->GetSprite()->GetRatio());
	//SetHeight(m_pSprite->GetFrameHeight() * m_pSprite->GetSprite()->GetRatio());

	//m_ground = 210 * m_pSprite->GetSprite()->GetRatio();

	m_pSprite->SetLooping(true);

	return (true);
}

void
Character::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->GetSprite()->SetX(static_cast<int>(m_x));
	m_pSprite->GetSprite()->SetY(static_cast<int>(m_y));
	m_pSprite->Draw(backBuffer);
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