#ifndef __TEXTURE_H__
#define __TEXTURE_H__

// Library includes:
#include <SDL.h>
#include <SDL_ttf.h>

// Forward Declarations:

class Texture
{
	//Member Methods:
public:
	Texture();
	~Texture();

	bool InitialiseImage(const char* pcFilename, SDL_Renderer* pRenderer);
	bool InitialiseFont(TTF_Font* pFont, const char* pcText, SDL_Renderer* pRenderer, SDL_Color* pColour);

	int GetWidth() const;
	int GetHeight() const;

	SDL_Texture* GetTexture();
	SDL_RendererFlip& GetFlip();

protected:

private:
	Texture(const Texture& texture);
	Texture& operator=(const Texture& texture);

	//Member Data:
public:

protected:
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;

	int m_width;
	int m_height;

	SDL_RendererFlip m_flip;

private:

};

#endif // __TEXTURE_H__
