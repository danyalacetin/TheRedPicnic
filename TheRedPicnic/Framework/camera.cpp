// This include:
#include "camera.h"

// Local includes:

// Library includes:
#include <cassert>

Camera* Camera::sm_pInstance = 0;

Camera::Camera()
{
}

Camera::~Camera()
{
}

bool
Camera::Initialise()
{
	m_position = 0;
	m_velocity = 0;
	return (true);
}

void Camera::CreateInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Camera();
		sm_pInstance->Initialise();
	}
}

Camera& Camera::GetInstance()
{

	return (*sm_pInstance);
}

void Camera::DestroyInstance()
{
	if (sm_pInstance)
	{
		delete sm_pInstance;
		sm_pInstance = nullptr;
	}
}

void
Camera::Process(float deltaTime)
{
	m_position = m_velocity * deltaTime;
	//m_velocity = 0;
}

float
Camera::GetVelocity()
{
	return m_velocity;
}

void
Camera::SetVelocity(float v)
{
	m_velocity = v;
}

int
Camera::GetPosition()
{
	return m_position;
}

void
Camera::SetPosition(int x)
{
	m_position = x;
}
