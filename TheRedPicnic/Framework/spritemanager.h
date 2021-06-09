#ifndef __SPRITEMANAGER_H__
#define __SPRITEMANAGER_H__
// Local Includes:

// Library Includes:

// Forward Declarations:
class Sprite;
class BackBuffer;

class SpriteManager
{
	//Member Methods:
public:
	SpriteManager();
	~SpriteManager();

	bool LoadSprites(BackBuffer& backBuffer);
	Sprite* GetSprite(int i);

protected:

private:
	
	//Member Data:
public:

protected:
	//-----Sprites-----

	// Main Menu
	Sprite* m_pTitleScreenSprite;
	Sprite* m_pButtonSprite;

	// Splash Screen
	Sprite* m_pFmodSprite;

	// Background
	Sprite* m_pBackgroundSprite;
	Sprite* m_pMidGroundSprite;
	Sprite* m_pGroundSprite;

	// Characters
	Sprite* m_pPlayerSprite;
	Sprite* m_pBunnySprite;
	Sprite* m_pSquirrelSprite;

	// Objects
	Sprite* m_pAppleSprite;
	Sprite* m_pChickenSprite;
	Sprite* m_pMuffinSprite;
	Sprite* m_pPieSprite;


private:

};

#endif //!__SPRITEMANAGER_H__