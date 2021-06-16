#ifndef __ANIMATEDSPRITE_H__
#define __ANIMATEDSPRITE_H__

class BackBuffer;
class Sprite;

class AnimatedSprite
{
	// Methods:
public:
	AnimatedSprite();
	~AnimatedSprite();

	bool Initialise(Sprite* sprite);

	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);

	Sprite* GetSprite();

	void SetWidth(int w);
	void SetHeight(int h);
	int GetWidth();
	int GetHeight();


	void SetFrameSpeed(float f);

	void SetFrameWidth(int w);
	void SetFrameHeight(int h);
	int GetFrameWidth();
	int GetFrameHeight();

	void SetFrameX(int x);
	void SetFrameY(int y);
	int GetFrameX();
	int GetFrameY();

	void SetPause(bool p);
	bool IsPaused();

	bool IsAnimating();
	void StartAnimating();

	bool IsLooping();
	void SetLooping(bool b);

	void SetFlipped(bool b);
	bool GetFlipped();

protected:

private:

	// Fields:
public:

protected:
	Sprite* m_sprite;
	int m_width;
	int m_height;

	float m_frameSpeed;
	float m_timeElapsed;

	int m_frameWidth;
	int m_frameHeight;
	int m_frameX;
	int m_frameY;

	bool m_paused;
	bool m_loop;
	bool m_animating;

	bool m_flipped;

private:

};

#endif // __ANIMATEDSPRITE_H__
