#ifndef __CAMERA_H__
#define __CAMERA_H__

class Camera
{
	//Member Methods:
public:
	~Camera();

	static void CreateInstance();
	static Camera& GetInstance();
	static void DestroyInstance();

	bool Initialise();
	void Process(float deltaTime);

	float GetVelocity();
	void SetVelocity(float v);

	int GetPosition();
	void SetPosition(int x);

protected:


private:
	Camera();

	//Member Data:
public:

protected:
	static Camera* sm_pInstance;

	int m_position;
	float m_velocity;

private:

};

#endif //__CAMERA_H__
