// This include:
#include "spritemanager.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"
#include "gameutils.h"

// Library includes:

SpriteManager::SpriteManager()
{
	
}

SpriteManager::~SpriteManager()
{
	//----Delete-Sprites----

// Main Menu
	delete m_pTitleScreenSprite;
	m_pTitleScreenSprite = 0;
	delete m_pButtonSprite;
	m_pButtonSprite = 0;

	// Splash Screen
	delete m_pFmodSprite;
	delete m_pSoundSprite;

	// Background
	delete m_pBackgroundSprite;
	delete m_pMidGroundSprite;
	delete m_pGroundSprite;

	// Characters
	delete m_pPlayerSprite;
	delete m_pBunnySprite;
	delete m_pSquirrelSprite;
	delete m_pRaccoonSprite;

	// Objects
	delete m_pAppleSprite;
	delete m_pChickenSprite;
	delete m_pMuffinSprite;
	delete m_pPieSprite;
}

bool 
SpriteManager::LoadSprites(BackBuffer& backBuffer)
{
	// Main Menu
	m_pTitleScreenSprite = backBuffer.CreateSprite("assets/Title.png");
	m_pButtonSprite = backBuffer.CreateSprite("assets/Button.png");

	// Splash Screen
	m_pFmodSprite = backBuffer.CreateSprite("assets/splashes/Sound.png");
	m_pSoundSprite = backBuffer.CreateSprite("assets/splashes/Music.png");

	// Background
	m_pBackgroundSprite = backBuffer.CreateSprite("assets/Background.png");
	m_pMidGroundSprite = backBuffer.CreateSprite("assets/Midground.png");
	m_pGroundSprite = backBuffer.CreateSprite("assets/Ground.png");

	// Characters
	m_pPlayerSprite = backBuffer.CreateSprite("assets/PlayerSpriteSheet.png");
	m_pBunnySprite = backBuffer.CreateSprite("assets/Bunny.png");
	m_pSquirrelSprite = backBuffer.CreateSprite("assets/Squirrel.png");
	m_pRaccoonSprite = backBuffer.CreateSprite("assets/Raccoon.png");

	// Objects
	m_pAppleSprite = backBuffer.CreateSprite("assets/FoodSpriteApple.png");
	m_pChickenSprite = backBuffer.CreateSprite("assets/FoodSpriteChicken.png");
	m_pMuffinSprite = backBuffer.CreateSprite("assets/FoodSpriteMuffin.png");
	m_pPieSprite = backBuffer.CreateSprite("assets/FoodSpritePieSlice.png");

	return true;
}

Sprite* 
SpriteManager::GetSprite(int i)
{
	switch(i)
	{
	case TITLE:
		return m_pTitleScreenSprite;
	case BUTTON:
		return m_pButtonSprite;
	case FMODSPRITE:
		return m_pFmodSprite;
	case SOUNDSPRITE:
		return m_pSoundSprite;
	case BACKGROUND:
		return m_pBackgroundSprite;
	case MIDGROUND:
		return m_pMidGroundSprite;
	case GROUND:
		return m_pGroundSprite;
	case PLAYER:
		return m_pPlayerSprite;
	case BUNNY:
		return m_pBunnySprite;
	case SQUIRREL:
		return m_pSquirrelSprite;
	case RACCOON:
		return m_pRaccoonSprite;
	case APPLE:
		return m_pAppleSprite;
	case CHICKEN:
		return m_pChickenSprite;
	case MUFFIN:
		return m_pMuffinSprite;
	case PIE:
		return m_pPieSprite;
	}
}