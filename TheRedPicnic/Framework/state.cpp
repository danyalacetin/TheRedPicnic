// This include:
#include "state.h"

// Local includes:
#include "gameutils.h"

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

StateType
State::GetStateType()
{
	return m_type;
}