#ifndef __TEXT_H__
#define __TEXT_H__

// Local Includes:
#include "gameutils.h"

// Library Includes:
#include<string>

// Forward Declarations:
class Texture;

struct TextDef
{
	unsigned alpha = 255;
	unsigned red = 255;
	unsigned green = 255;
	unsigned blue = 255;
	unsigned size = 28;

	void SetColour(int red, int green, int blue);
	std::string toString();
};

class Text
{
	//Member Methods:
public:
	Text(Texture* pTexture);
	~Text();

	int GetWidth() const;
	int GetHeight() const;

	void SetAlignment(TextAlignment newAlignment);
	TextAlignment GetAlignment() const;

	Texture& GetTexture() const;

protected:

private:
	Text(const Text& text);
	Text& operator=(const Text& text);


	//Member Data:
public:

protected:
	int m_iWidth;
	int m_iHeight;

	Texture* m_pTexture;
	TextAlignment m_textAlignment;

private:

};

#endif //!__TEXT_H__
