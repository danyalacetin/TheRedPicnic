/*	Remeber to credit song maker
 *
 *	Music: Evan King - Dingos
 *	https ://www.youtube.com/channel/UCT1ZkP03V18LmOj8zbyP-Dw?
 *	https ://contextsensitive.bandcamp.com/
 *
 */

// This include:
#include "soundmanager.h"

// Local includes:


// Library includes:
#include <fmod.hpp>
#include<String.h>

SoundManager* SoundManager::sm_pInstance = 0;

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

bool SoundManager::Initialise()
{
	m_volume = 0.5f;
	LoadSounds();
	PlaySound(MUSIC); 
	return (true);
}

SoundManager& SoundManager::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new SoundManager();
		sm_pInstance->Initialise();
	}

	return (*sm_pInstance);
}

void SoundManager::DestroyInstance()
{
	if (sm_pInstance)
	{
		delete sm_pInstance;
		sm_pInstance = nullptr;
	}
}

bool
SoundManager::LoadSounds()
{
	// Create the main system object.
	FMOD::System_Create(&m_pSystem);

	// Initialize FMOD.
	m_pSystem->init(512, FMOD_INIT_NORMAL, nullptr);

	// Create the sound.
	m_pSystem->createSound("assets/sounds/buttonSelect.wav", FMOD_DEFAULT, nullptr, &m_pButtonSelected);
	m_pSystem->createSound("assets/sounds/buttonPress.wav", FMOD_DEFAULT, nullptr, &m_pButtonPress);
	m_pSystem->createSound("assets/sounds/playerHurt.wav", FMOD_DEFAULT, nullptr, &m_pPlayerHurt);
	m_pSystem->createSound("assets/sounds/gameStart.wav", FMOD_DEFAULT, nullptr, &m_pGameStart);
	m_pSystem->createSound("assets/music/dingos.wav", FMOD_LOOP_NORMAL, nullptr, &m_pBackgroundMusic);

	//Channel::isPlaying
	return 0;
}

void SoundManager::PlaySound(Sounds sound)
{
	switch (sound)
	{
	case BUTTONPRESS:
		m_pSystem->playSound(m_pButtonPress, NULL, false, NULL);
		break;
	case BUTTONSELECT:
		m_pSystem->playSound(m_pButtonSelected, NULL, false, NULL);
		break;
	case PLAYERHURT:
		m_pSystem->playSound(m_pPlayerHurt, NULL, false, NULL);
		break;
	case GAMESTART:
		m_pSystem->playSound(m_pGameStart, NULL, false, NULL);
		break;
	case MUSIC:
		m_pSystem->playSound(m_pBackgroundMusic, NULL, false, &m_pMusicChannel);
		m_musicPlaying = true;
		break;
	}
	m_pMusicChannel->setVolume(m_volume);
	//m_pSoundChannel->setVolume(m_volume);
}


void SoundManager::ToggleMusic()
{
	if (m_musicPlaying == true)
	{
		m_pMusicChannel->stop();
		m_musicPlaying = false;
	}
	else
	{
		PlaySound(MUSIC);
	}
}

void SoundManager::IncreaseVol()
{
	if (m_volume <= 0.9f)
	{
		m_volume += 0.1f;
		m_pMusicChannel->setVolume(m_volume);
		//m_pSoundChannel->setVolume(m_volume);
	}
}

void SoundManager::DecreaseVol()
{
	if (m_volume >= 0.1f)
	{
		m_volume -= 0.1f;
		m_pMusicChannel->setVolume(m_volume);
		//m_pSoundChannel->setVolume(m_volume);
	}
}

void SoundManager::Update()
{
	m_pSystem->update();
}