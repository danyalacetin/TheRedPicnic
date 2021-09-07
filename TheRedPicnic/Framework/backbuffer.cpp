// This include:
#include "backbuffer.h"

// Local includes:
#include "logmanager.h"
#include "sprite.h"
#include "animatedsprite.h"
#include "resourcemanager.h"
#include "texturemanager.h"
#include "texture.h"
#include "text.h"

// Library includes:
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>

BackBuffer::BackBuffer()
	: m_pWindow(0)
	, m_pRenderer(0)
	, m_width(0)
	, m_height(0)
	, m_clearRed(0)
	, m_clearGreen(0)
	, m_clearBlue(0)
{

}

BackBuffer::~BackBuffer()
{
	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = 0;

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = 0;

	IMG_Quit();
	SDL_Quit();
}

bool
BackBuffer::Initialise(int width, int height)
{
	m_width = width;
	m_height = height;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		LogSDLError();
		return (false);
	}
	else
	{
		m_pWindow = SDL_CreateWindow("COMP710 2D Game Framework", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

		if (m_pWindow == 0)
		{
			LogSDLError();
			return (false);
		}
		else
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (m_pRenderer == 0)
			{
				LogSDLError();
				return (false);
			}
			else
			{
				int imageResult = IMG_Init(IMG_INIT_PNG);

				if (imageResult == 0)
				{
					LogSDLError();
					return (false);
				}
			}
		}
	}

	SetFullscreen(true);
	SDL_Delay(1000);

	return (true);
}

SDL_Renderer*
BackBuffer::GetRenderer()
{
	return (m_pRenderer);
}

void
BackBuffer::SetFullscreen(bool fullscreen)
{
	if (fullscreen)
	{
		//		SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALWAYS_ON_TOP);
		SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_ALWAYS_ON_TOP);
		SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
		SDL_SetWindowSize(m_pWindow, m_width, m_height);
	}
	else
	{
		SDL_SetWindowFullscreen(m_pWindow, 0);
	}
}

void
BackBuffer::Clear()
{
	SDL_SetRenderDrawColor(m_pRenderer, m_clearRed, m_clearGreen, m_clearBlue, 0xff);
	SDL_RenderClear(m_pRenderer);
}

void
BackBuffer::Present()
{
	SDL_RenderPresent(m_pRenderer);
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b)
{
	SetDrawColour(r, g, b, 0xFF);
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	SDL_SetRenderDrawColor(m_pRenderer, r, g, b, a);
}

void
BackBuffer::DrawSprite(Sprite& sprite)
{
	SDL_Rect dest;

	dest.x = sprite.GetX() - sprite.GetWidth()/2;
	dest.y = sprite.GetY() - sprite.GetHeight()/2;
	dest.w = sprite.GetWidth();
	dest.h = sprite.GetHeight();

	SDL_SetTextureBlendMode(sprite.GetTexture()->GetTexture(), SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(sprite.GetTexture()->GetTexture(), sprite.GetAlpha());

	float fAngle = -sprite.GetAngle() * 180.0f / static_cast<float>(M_PI);

	SDL_RenderCopyEx(m_pRenderer, sprite.GetTexture()->GetTexture(), nullptr, &dest,
		fAngle, nullptr, sprite.GetTexture()->GetFlip());
}

void
BackBuffer::DrawAnimatedSprite(AnimatedSprite& animatedSprite)
{
	SDL_Rect dest;
	SDL_Rect source;

	dest.x = animatedSprite.GetSprite()->GetX() - animatedSprite.GetWidth()/2;
	dest.y = animatedSprite.GetSprite()->GetY() - animatedSprite.GetHeight()/2;
	dest.w = animatedSprite.GetWidth();
	dest.h = animatedSprite.GetHeight();

	source.x = animatedSprite.GetFrameX();
	source.y = animatedSprite.GetFrameY();
	source.w = animatedSprite.GetFrameWidth();
	source.h = animatedSprite.GetFrameHeight();

	if (animatedSprite.GetFlipped()) {
		m_flip = SDL_FLIP_HORIZONTAL;
	}
	else {
		m_flip = SDL_FLIP_NONE;
	}

	SDL_RenderCopyEx(m_pRenderer, animatedSprite.GetSprite()->GetTexture()->GetTexture(), &source, &dest, animatedSprite.GetSprite()->GetAngle(), NULL, m_flip);
}

void
BackBuffer::DrawRectangle(int x1, int y1, int x2, int y2)
{
	SDL_Rect fillRect;

	fillRect.x = x1;
	fillRect.y = y1;
	fillRect.w = x2 - x1;
	fillRect.h = y2 - y1;

	SDL_RenderFillRect(m_pRenderer, &fillRect);
}

void
BackBuffer::DrawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(m_pRenderer, x1, y1, x2, y2);
}

void
BackBuffer::LogSDLError()
{
	LogManager::GetInstance().Log(SDL_GetError());
}

Sprite*
BackBuffer::CreateSprite(const char* pcFilename)
{
	Texture* pTexture = ResourceManager::GetInstance().GetTextureManager().GetTexture(pcFilename);

	Sprite* pSprite = new Sprite();
	if (!pSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("Sprite Failed to Initialise!");
	}

	return (pSprite);
}

void
BackBuffer::SetClearColour(unsigned char r, unsigned char g, unsigned char b)
{
	m_clearRed = r;
	m_clearGreen = g;
	m_clearBlue = b;
}

void
BackBuffer::DrawText(Text* pText, int iX, int iY) // TODO change handles
{
	if (pText)
	{
		TextAlignment alignment = pText->GetAlignment();
		Texture& pTexture = pText->GetTexture();
		SDL_Rect dst;

		switch (alignment)
		{
		case ALIGN_BOT_LEFT:
			dst.x = iX;
			dst.y = iY - pText->GetHeight();
			dst.w = pText->GetWidth();
			dst.h = pText->GetHeight();
			break;
		case ALIGN_CENTRE:
			dst.x = iX - pText->GetWidth() / 2;
			dst.y = iY - pText->GetHeight() / 2;
			dst.w = pText->GetWidth();
			dst.h = pText->GetHeight();
			break;
		default:
			break;
		}

		SDL_RenderCopy(m_pRenderer, pTexture.GetTexture(), NULL, &dst);
	}
}