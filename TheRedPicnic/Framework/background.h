// COMP710 GP 2D Framework 2019
#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

// Forward Declarations:
class Game;
class BackBuffer;
class Sprite;

class Background
{
	//Member Methods:
public:
	Background();
	~Background();

	bool Initialise(Sprite* m_pBackroundSprite, Sprite* m_pMidgroundSprite, Sprite* m_pGroundSprite);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	int GetBackgroundX(int i);
	void SetBackgroundX(int i, int x);

	int GetMidgroundX(int i);
	void SetMidgroundX(int i, int x);

	int GetGroundX(int i);
	void SetGroundX(int i, int x);

	void SetCameraVelocity(float f);

protected:

private:

	//Member Data:
public:

protected:
	Sprite* m_pBackgroundSprite;
	Sprite* m_pMidgroundSprite;
	Sprite* m_pGroundSprite;

	int m_backgroundX[3];
	int m_midgroundX[3];
	int m_groundX[3];

	float m_cameraVelocity;

private:


};

#endif //__BACKGROUND_H__
