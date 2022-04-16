#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

// Local Includes:

// Library Includes:
#include <string>
#include <fmod.hpp>

// Forward Declarations:

enum Sounds
{
	BUTTONPRESS,
	BUTTONSELECT,
	PLAYERHURT,
	PLAYERJUMP,
	GAMESTART
};

enum Music
{
	TITLEMUSIC,
	BACKGROUNDMUSIC
};

enum Channels
{
	SOUNDCHANNEL,
	MUSICCHANNEL
};

class SoundManager
{
	//Member Methods:
public:
	SoundManager();
	~SoundManager();

	bool Initialise();

	static SoundManager& GetInstance();
	static void DestroyInstance();

	bool LoadSounds();
	void PlaySound(Sounds sound);
	void PlayMusic(Music music);

	void ToggleMusic();

	void IncreaseVol();
	void DecreaseVol();
	float GetVolume();

	void Update();

	//void SetFileLocation(std::string location);

protected:


private:

	//Member Data:
public:

protected:
	static SoundManager* sm_pInstance;
	FMOD::System* m_pSystem;

	FMOD::Channel* m_pMusicChannel;
	FMOD::Channel* m_pSoundChannel;

	//Sound Effects
	FMOD::Sound* m_pButtonSelected;
	FMOD::Sound* m_pButtonPress;
	FMOD::Sound* m_pPlayerHurt;
	FMOD::Sound* m_pGameStart;
	FMOD::Sound* m_pPlayerJump;

	//Music
	FMOD::Sound* m_pTitleMusic;
	FMOD::Sound* m_pBackgroundMusic;

	bool m_bIsInitialised;
	std::string m_folderLocation;

	Music m_music;

	bool m_musicPlaying;
	float m_volume;

private:

};

#endif //!__SOUNDMANAGER_H__
