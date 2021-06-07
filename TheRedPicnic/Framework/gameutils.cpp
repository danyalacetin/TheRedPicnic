// This include:
#include "gameutils.h"

// Local includes:

// Library includes:

Vector2f::Vector2f()
	: x(0.0f)
	, y(0.0f)
{
}

Vector2f::Vector2f(float fX, float fY)
	: x(fX)
	, y(fY)
{
}

Vector2f::Vector2f(int iX, int iY)
	: x(static_cast<float>(iX))
	, y(static_cast<float>(iY))
{
}

Vector2f Vector2f::FromIntVector(Vector2i vec)
{
	float fX = static_cast<float>(vec.x);
	float fY = static_cast<float>(vec.y);

	return Vector2f(fX, fY);
}

Vector2i Vector2f::ToIntVector() const
{
	int iX = static_cast<int>(x);
	int iY = static_cast<int>(y);

	return Vector2i(iX, iY);
}

Vector2i::Vector2i()
	: x(0)
	, y(0)
{
}

Vector2i::Vector2i(int iX, int iY)
	: x(iX)
	, y(iY)
{
}
