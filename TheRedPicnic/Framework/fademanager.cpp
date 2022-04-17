// This include:
#include "fademanager.h"

// Local includes

// Library includes:

FadeManager* FadeManager::sm_pInstance = 0;

FadeManager::FadeManager()
{
}

FadeManager::~FadeManager()
{
}

bool FadeManager::Initialise()
{
	m_fade = FADEDOUT;
	m_fadeOpacity = 255.0f;
	m_fadeDuration = 2.0f;

	return (true);
}

FadeManager& FadeManager::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new FadeManager();
		sm_pInstance->Initialise();
	}

	return (*sm_pInstance);
}

void FadeManager::DestroyInstance()
{
	if (sm_pInstance)
	{
		delete sm_pInstance;
		sm_pInstance = nullptr;
	}
}

void FadeManager::Process(float deltaTime)
{

}

void FadeManager::Draw(BackBuffer& backBuffer)
{
}

void FadeManager::FadeOut(float duration)
{
}

void FadeManager::FadeIn(float duration)
{
}
