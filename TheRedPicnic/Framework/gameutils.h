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

enum SpriteCode 
{
	TITLE,
	BUTTON,
	FMODSPRITE,
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
	MainMenu,
	InGame,
	InGameMenu
};

enum NpcState
{
	IDLE,
	WALKING,
	RUNNING,
	EATING
};

#endif //!__GAMEUTILS_H__
