// This include:
#include "label.h"

// Local includes:
#include "fontmanager.h"
#include "resourcemanager.h"
#include "text.h"
#include "backbuffer.h"

// Library includes:

Label::Label()
	: UiElement()
	, m_pText(0)
	, m_textAlignment(ALIGN_CENTRE)
{
	m_fontFilename = "assets/ORANGEKI.ttf";
}

Label::~Label()
{
}

bool Label::Initialise(std::string text)
{
	m_text = text;

	FontManager& manager = ResourceManager::GetInstance().GetFontManager();
	m_pText = manager.GetText(m_fontFilename, m_text, m_textDef);

	float fWidth = static_cast<float>(m_pText->GetWidth());
	float fHeight = static_cast<float>(m_pText->GetHeight());

	Vector2f dimensions = Vector2f(fWidth, fHeight);

	UiElement::SetDimensions(dimensions);

	return (true);
}

void Label::Draw(BackBuffer& backBuffer)
{
	FontManager& manager = ResourceManager::GetInstance().GetFontManager();
	m_pText = manager.GetText(m_fontFilename, m_text, m_textDef);

	Vector2f position = UiElement::GetPosition();
	m_pText->SetAlignment(m_textAlignment); // TODO does this belong here???

	backBuffer.DrawText(m_pText, static_cast<int>(position.x), static_cast<int>(position.y));
}

void Label::SetText(std::string text)
{
	m_text = text;
}

void Label::SetColour(int r, int g, int b)
{
	m_textDef.red = r;
	m_textDef.green = g;
	m_textDef.blue = b;
}

void Label::SetSize(int size)
{
	m_textDef.size = size;
}

void Label::SetFont(std::string filename)
{
	m_fontFilename = filename;
}

void Label::SetAlignment(TextAlignment newAlignment)
{
	m_textAlignment = newAlignment;
}


void Label::PositionChildren()
{

}
