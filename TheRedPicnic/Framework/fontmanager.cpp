// This include:
#include "fontmanager.h"

// Local includes
#include "logmanager.h"
#include "text.h"
#include "texture.h"

// Library includes:
#include <sstream>
#include <SDL_ttf.h>
#include <SDL.h>

FontManager::FontManager(SDL_Renderer* pRenderer)
	: m_pRenderer(0)
{
	TTF_Init();
	m_pRenderer = pRenderer;
}

FontManager::~FontManager()
{
	for (std::pair<std::string, TTF_Font*> entry : m_loadedFonts)
	{
		TTF_CloseFont(entry.second);
	}

	for (std::pair<std::string, Text*> entry : m_loadedTexts)
	{
		delete entry.second;
	}

	m_loadedFonts.clear();
	m_loadedTexts.clear();
	m_pRenderer = nullptr;
}

Text* FontManager::GetText(std::string filename, std::string text, TextDef& textDef)
{
	Text* pText = 0;
	std::string filepath = filename;
	std::string id = filename + "-" + text + "-" + textDef.toString();

	if (m_loadedTexts.find(id) == m_loadedTexts.end())
	{
		// Not already loaded... so load...

		SDL_Color colour;
		colour.a = textDef.alpha;
		colour.r = textDef.red;
		colour.g = textDef.green;
		colour.b = textDef.blue;

		TTF_Font* pFont = GetFont(filename, textDef.size);
		Texture* pTexture = new Texture();
		pTexture->InitialiseFont(pFont, text.c_str(), m_pRenderer, &colour);

		pText = new Text(pTexture);

		m_loadedTexts[id] = pText;
	}
	else
	{
		// Is already loaded...
		pText = m_loadedTexts[id];
	}

	return (pText);
}

TTF_Font* FontManager::GetFont(std::string filename, unsigned size)
{
	TTF_Font* pFont = 0;
	std::string filepath = filename;
	std::string id = filename + "-" + std::to_string(size);

	if (m_loadedFonts.find(id) == m_loadedFonts.end())
	{
		// Not already loaded... so load...
		pFont = TTF_OpenFont(filepath.c_str(), size);

		if (pFont == 0)
		{
			char buff[64];

			sprintf_s(buff, "Font file (%s) with size %d failed to initialise!", filepath.c_str(), size);

			LogManager::GetInstance().Log(buff);
		}

		m_loadedFonts[id] = pFont;
	}
	else
	{
		// Is already loaded...
		pFont = m_loadedFonts[id];
	}

	return (pFont);
}

