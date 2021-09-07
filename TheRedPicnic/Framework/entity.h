#ifndef __ENTITY_H__
#define __ENTITY_H__

// Forward Declarations:
class BackBuffer;
class Sprite;

class Entity
{
	//Member Methods:
public:
	Entity();
	~Entity();


	bool Initialise(Sprite* sprite);

	void Process(float deltaTime);
	void ProcessFlash(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void ProcessMovement(float deltaTime);

	void SetDead(bool dead);
	bool IsDead() const;

	bool IsCollidingWith(Entity& e);

	void SetPosition(float x, float y);
	void SetPositionX(float x);
	void SetPositionY(float y);

	float GetPositionX() const;
	float GetPositionY() const;

	void SetWidth(float w);
	float GetWidth();

	void SetHeight(float h);
	float GetHeight();

	float GetHorizontalVelocity() const;
	void SetHorizontalVelocity(float x); 

	float GetVerticalVelocity() const;
	void SetVerticalVelocity(float y);

	float GetMaxHorizontalVelocity() const;
	void SetMaxHorizontalVelocity(float x);

	float GetMaxVerticalVelocity() const;
	void SetMaxVerticalVelocity(float y);

	bool IsGrounded();

	bool IsPushed();
	void SetPushed(bool b);

	bool IsFlashing();
	void SetFlashing(bool b);

protected:

private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);

	//Member Data:
public:

protected:
	Sprite* m_pSprite;

	float m_x;
	float m_y;

	float m_height;
	float m_width;

	float m_velocityX;
	float m_velocityY;

	float m_maxVelocityX;
	float m_maxVelocityY;

	float m_flashTime;
	bool m_flashing;
	bool m_hidden;


	bool m_grounded;
	bool m_pushed;
	bool m_dead;

private:

};

#endif //__ENTITY_H__
