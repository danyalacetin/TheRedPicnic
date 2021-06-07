#ifndef __FONTMANAGER_H__
#define __FONTMANAGER_H__

// Local Includes:

// Library Includes:
#include <map>
#include <string>
#include <SDL_ttf.h>

// Forward Declarations:
class Text;
struct TextDef;
struct SDL_Renderer;

class FontManager
{
	//Member Methods:
public:
	FontManager(SDL_Renderer* pRenderer);
	~FontManager();

	Text* GetText(std::string filename, std::string text, TextDef& textDef);

protected:
	TTF_Font* GetFont(std::string filename, unsigned size);

private:
	FontManager(const FontManager& fontmanager);
	FontManager& operator=(const FontManager& fontmanager);


	//Member Data:
public:

protected:
	std::map<std::string, TTF_Font*> m_loadedFonts;
	std::map<std::string, Text*> m_loadedTexts;
	SDL_Renderer* m_pRenderer;

private:

};

#endif //!__FONTMANAGER_H__
