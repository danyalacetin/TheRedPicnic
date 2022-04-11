#ifndef __SPLASHSCREEN_H__
#define __SPLASHSCREEN_H__

class BackBuffer;
class Sprite;

class SplashScreen
{
public:
	//Member Methods:
	SplashScreen();
	~SplashScreen();
	bool Initialise(Sprite* sprite);
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	bool Isfinished();
	void Setfinished();

protected:

private:

	//Member Data:
public:

protected:
	Sprite* m_pSprite;
	float m_fTime;
	float m_maxDuration;
	float m_holdDuration;
	bool m_finished;

private:

};

#endif // __SPLASHSCREEN_H__


