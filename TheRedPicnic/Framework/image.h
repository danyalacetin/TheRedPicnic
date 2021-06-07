#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "uielement.h"

class BackBuffer;
class Sprite;

class Image : public UiElement
{
public:
	//Member Methods:
	Image();
	~Image();
	bool Initialise(Sprite* sprite);
	void Draw(BackBuffer& backBuffer);

	void PositionChildren();

protected:

private:

	//Member Data:
public:

protected:

private:
	Sprite* m_pSprite;

};

#endif // __IMAGE_H__


