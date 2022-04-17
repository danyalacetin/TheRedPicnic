#ifndef __GAMEUTILS_H__
#define __GAMEUTILS_H__

// Local Includes:

// Library Includes:

// Forward Declarations:

struct Vector2i
{
	Vector2i();
	Vector2i(int iX, int iY);

	int x;
	int y;
};

struct Vector2f
{
	Vector2f();
	Vector2f(float fX, float fY);
	Vector2f(int iX, int iY);

	static Vector2f FromIntVector(Vector2i vec);
	Vector2i ToIntVector() const;

	float x;
	float y;
};

enum TextAlignment
{
	ALIGN_BOT_LEFT,
	ALIGN_CENTRE,
};

enum Fade
{
	FADINGIN,	//getting lighter
	FADINGOUT,	//getting darker
	FADEDIN,	//no black
	FADEDOUT	//all black
};

enum SpriteCode 
{
	TITLE,
	BUTTON,
	FMODSPRITE,
	SOUNDSPRITE,
	BACKGROUND,
	MIDGROUND,
	GROUND,
	PLAYER,
	BUNNY,
	SQUIRREL,
	RACCOON,
	APPLE,
	CHICKEN,
	MUFFIN,
	PIE
};

enum StateType
{
	InGameMenu,
	InGame,
	MainMenu
};

enum NpcState
{
	IDLE,
	WALKING,
	RUNNING,
	EATING
};

#endif //!__GAMEUTILS_H__
