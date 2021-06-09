// This include:
#include "resourcemanager.h"

// Local includes:
#include "texturemanager.h"
#include "fontmanager.h"
#include "logmanager.h"
#include "inputhandler.h"
#include "spritemanager.h"

// Library includes:

ResourceManager* ResourceManager::sm_pInstance = 0;

ResourceManager::ResourceManager()
	: m_pTextureManager(0)
	, m_pFontManager(0)
	, m_pInputHandler(0)
	, m_bIsInitialised(false)
{

}

ResourceManager::~ResourceManager()
{
	delete m_pFontManager;
	m_pFontManager = nullptr;

	delete m_pTextureManager;
	m_pTextureManager = nullptr;

	delete m_pInputHandler;
	m_pInputHandler = nullptr;

	delete m_pSpriteManager;
	m_pSpriteManager = nullptr;
}

bool ResourceManager::Initialise(SDL_Renderer* pRenderer)
{
	bool bSuccess = true;

	m_pTextureManager = new TextureManager();
	m_pTextureManager->Initialise(pRenderer);

	m_pFontManager = new FontManager(pRenderer);
	m_pInputHandler = new InputHandler();
	m_pSpriteManager = new SpriteManager();

	m_bIsInitialised = true;

	return (true);
}

bool ResourceManager::Setup(SDL_Renderer* pRenderer)
{
	bool bSuccess = false;

	if (sm_pInstance == 0)
	{
		sm_pInstance = new ResourceManager();
		bSuccess = sm_pInstance->Initialise(pRenderer);
	}
	else
	{
		bSuccess = true;
	}

	return (bSuccess);
}

ResourceManager& ResourceManager::GetInstance()
{
	if (sm_pInstance == 0)
	{

		LogManager::GetInstance().Log("GetInstance called on ResourceManager before Setup.");
	}

	return (*sm_pInstance);
}

void ResourceManager::DestroyInstance()
{
	if (sm_pInstance)
	{
		delete sm_pInstance;
		sm_pInstance = nullptr;
	}
}

FontManager& ResourceManager::GetFontManager()
{
	FontManager* pFontManager = 0;

	if (m_bIsInitialised)
	{
		if (m_pTextureManager)
		{
			pFontManager = m_pFontManager;
		}
		else
		{
			LogManager::GetInstance().Log("Font Manager is null");
		}
	}
	else
	{
		LogManager::GetInstance().Log("Attempting to get FontManager before ResourceManager is initialised");
	}

	return (*pFontManager);
}

TextureManager& ResourceManager::GetTextureManager()
{
	TextureManager* pTextureManager = 0;

	if (m_bIsInitialised)
	{
		if (m_pTextureManager)
		{
			pTextureManager = m_pTextureManager;
		}
		else
		{
			LogManager::GetInstance().Log("Texture Manager is null");
		}
	}
	else
	{
		LogManager::GetInstance().Log("Attempting to get TextureManager before ResourceManager is initialised");
	}

	return (*pTextureManager);
}

InputHandler& ResourceManager::GetInputHandler()
{
	InputHandler* pInputHandler = 0;

	if (m_bIsInitialised)
	{
		if (m_pTextureManager)
		{
			pInputHandler = m_pInputHandler;
		}
		else
		{
			LogManager::GetInstance().Log("Input Handler is null");
		}
	}
	else
	{
		LogManager::GetInstance().Log("Attempting to get Input Handler before ResourceManager is initialised");
	}

	return (*pInputHandler);
}

SpriteManager& ResourceManager::GetSpriteManager()
{
	SpriteManager* pSpriteManager = 0;

	if (m_bIsInitialised)
	{
		if (m_pTextureManager)
		{
			pSpriteManager = m_pSpriteManager;
		}
		else
		{
			LogManager::GetInstance().Log("Sprite Manager is null");
		}
	}
	else
	{
		LogManager::GetInstance().Log("Attempting to get Sprite Manager before ResourceManager is initialised");
	}

	return (*pSpriteManager);
}