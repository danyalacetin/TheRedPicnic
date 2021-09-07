// This include:
#include "gamemenustate.h"

// Local includes:
#include "game.h"
#include "state.h"
#include "button.h"
#include "resourcemanager.h"
#include "inputhandler.h"

// Library includes:
#include <cassert>

GameMenuState::GameMenuState()
	: State()
{
}

GameMenuState::~GameMenuState()
{
	while (!m_menuStack.empty())
	{
		delete m_menuStack.top();
		m_menuStack.pop();
	}
}

bool
GameMenuState::Initialise(Sprite* pButton)
{
	m_type = InGameMenu;

	m_pButtonSprite = pButton;
	CreateGameMenu();
	return (true);
}

void
GameMenuState::Process(float deltaTime)
{
	m_menuStack.top()->Process(deltaTime);

	if (m_menuStack.top()->GetSelectionCooldown() <= 0)
	{
		if (ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_RETURN))
		{
			EnterButtonPressed();
		}

		else if (ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_UP))
		{
			UpButtonPressed();
		}

		else if (ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_DOWN))
		{
			DownButtonPressed();
		}

		else if (ResourceManager::GetInstance().GetInputHandler().GetKeyPressed(SDLK_ESCAPE))
		{
			ResourceManager::GetInstance().GetInputHandler().SetKeyPressed(SDLK_ESCAPE, false);
			EscapeButtonPressed();
		}
	}

}

void
GameMenuState::Draw(BackBuffer& backBuffer)
{
	m_menuStack.top()->Draw(backBuffer);
}

void
GameMenuState::CreateGameMenu()
{
	m_pGameMenu = new Menu();
	m_pGameMenu->Initialise();

	m_pButton = new Button();
	m_pButton->Initialise(m_pButtonSprite, "Resume");
	m_pButton->SetSelected(true);
	m_pButton->SetOnPress([&] {Game::GetInstance().DeleteState(); });
	m_pGameMenu->AddButton(m_pButton);

	m_pButton = new Button();
	m_pButton->Initialise(m_pButtonSprite, "Main Menu");
	m_pButton->SetOnPress([&] {Game::GetInstance().DeleteState(); Game::GetInstance().DeleteState(); });
	m_pGameMenu->AddButton(m_pButton);

	m_pButton = new Button();
	m_pButton->Initialise(m_pButtonSprite, "Quit");
	m_pButton->SetOnPress([] { Game::GetInstance().Quit(); });
	m_pGameMenu->AddButton(m_pButton);

	m_pGameMenu->PositionElements(Game::m_screenDimensions);

	m_menuStack.push(m_pGameMenu);
}

void
GameMenuState::UpButtonPressed()
{
	int iselected;

	iselected = m_menuStack.top()->DecrementSelected();

	for (unsigned i = 0; i < m_menuStack.top()->GetButtonContainor().size(); i++)
	{
		if (i == iselected)
		{
			m_menuStack.top()->GetButtonContainor()[i]->SetSelected(true);
		}
		else
		{
			m_menuStack.top()->GetButtonContainor()[i]->SetSelected(false);
		}
	}
}

void
GameMenuState::DownButtonPressed()
{
	int iselected;

	iselected = m_menuStack.top()->IncrementSelected();

	for (unsigned i = 0; i < m_menuStack.top()->GetButtonContainor().size(); i++)
	{
		if (i == iselected)
		{
			m_menuStack.top()->GetButtonContainor()[i]->SetSelected(true);
		}
		else
		{
			m_menuStack.top()->GetButtonContainor()[i]->SetSelected(false);
		}
	}
}

void
GameMenuState::EnterButtonPressed()
{
	m_menuStack.top()->GetSelectedButton().OnPress();
}

void
GameMenuState::EscapeButtonPressed()
{
	Game::GetInstance().DeleteState();
}
