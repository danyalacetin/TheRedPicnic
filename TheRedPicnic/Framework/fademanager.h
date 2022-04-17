#ifndef __FADEMANAGER_H__
#define __FADEMANAGER_H__

// Local Includes:
#include "gameutils.h"

// Library Includes:

class BackBuffer;

// Forward Declarations:


class FadeManager
{
	//Member Methods:
public:

	FadeManager();
	~FadeManager();

	bool Initialise();

	static FadeManager& GetInstance();
	static void DestroyInstance();

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void FadeOut(float duration);
	void FadeIn(float duration);

protected:

private:
	FadeManager(const FadeManager& fademanager);
	FadeManager& operator=(const FadeManager& fademanager);


	//Member Data:
public:

protected:
	static FadeManager* sm_pInstance;

	Fade m_fade;
	float m_fadeDuration;
	float m_fadeOpacity;

private:


};

#endif //!__FONTMANAGER_H__
