#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

// Local Includes:

// Library Includes:
#include <string>

// Forward Declarations:
class TextureManager;
class IniManager;
struct SDL_Renderer;
class FontManager;
class InputHandler;
class SpriteManager;

class ResourceManager
{
	//Member Methods:
public:
	~ResourceManager();

	static bool Setup(SDL_Renderer* pRenderer);
	static ResourceManager& GetInstance();
	static void DestroyInstance();

	FontManager& GetFontManager();
	TextureManager& GetTextureManager();
	InputHandler& GetInputHandler();
	SpriteManager& GetSpriteManager();

protected:
	bool Initialise(SDL_Renderer* pRenderer);

private:
	ResourceManager();
	ResourceManager(const ResourceManager& resourcemanager);
	ResourceManager& operator=(const ResourceManager& resourcemanager);


	//Member Data:
public:

protected:
	static ResourceManager* sm_pInstance;

	TextureManager* m_pTextureManager;
	FontManager* m_pFontManager;
	InputHandler* m_pInputHandler;
	SpriteManager* m_pSpriteManager;

	bool m_bIsInitialised;

private:

};

#endif //!__RESOURCEMANAGER_H__
