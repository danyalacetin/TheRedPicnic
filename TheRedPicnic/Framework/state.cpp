// This include:
#include "state.h"

// Local includes:

// Library includes:
#include <cassert>

State::State()
{
}

State::~State()
{
}

bool
State::Initialise()
{
	return (true);
}

void
State::Process(float deltaTime)
{
}

void
State::Draw(BackBuffer& backBuffer)
{
}

void
State::ProcessInputWait()
{
	if (m_inputwait > 0) 
	{
		m_inputwait--;
	}
}

int
State::GetInputWait()
{
	return m_inputwait;
}

void
State::SetInputWait(int i)
{
	m_inputwait = i;
}