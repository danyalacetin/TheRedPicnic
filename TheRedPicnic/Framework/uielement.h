#ifndef __UIELEMENT_H__
#define __UIELEMENT_H__

// Local Includes:
#include "gameutils.h"

// Library Includes:

// Forward Declarations:
class BackBuffer;

class UiElement
{
	//Member Methods:
public:
	virtual ~UiElement();

	virtual void Draw(BackBuffer& backBuffer) = 0;

	void SetPosition(Vector2f newPosition);
	void SetPosition(float fX, float fY);
	void SetPosition(int iX, int iY);
	Vector2f GetPosition();

	void SetDimensions(Vector2f newDimensions);
	Vector2f GetDimensions();

	virtual void PositionChildren() = 0;

protected:
	UiElement();

private:
	UiElement(const UiElement& uielement);
	UiElement& operator=(const UiElement& uielement);

	//Member Data:
public:

protected:
	Vector2f m_position;
	Vector2f m_dimensions;

private:

};

#endif //!__UIELEMENT_H__
