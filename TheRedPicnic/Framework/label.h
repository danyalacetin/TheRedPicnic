#ifndef __LABEL_H__
#define __LABEL_H__

// Superclass Includes:
#include "uielement.h"

// Local Includes:
#include "text.h"
#include "gameutils.h"

// Library Includes:
#include <string>

// Forward Declarations:
class BackBuffer;

class Label : public UiElement
{
	//Member Methods:
public:
	Label();
	~Label();

	bool Initialise(std::string text);
	void Draw(BackBuffer& backBuffer);

	void SetText(std::string text);
	void SetColour(int r, int g, int b);
	void SetSize(int size);
	void SetFont(std::string filename);

	void SetAlignment(TextAlignment newAlignment);

	void PositionChildren();

protected:

private:
	Label(const Label& label);
	Label& operator=(const Label& label);


	//Member Data:
public:

protected:
	Text* m_pText;
	std::string m_text;

	std::string m_fontFilename;
	TextDef m_textDef;
	TextAlignment m_textAlignment;

private:

};

#endif //!__LABEL_H__
