// This include:
#include "menustate.h"

// Local includes:
#include "sprite.h"
#include "game.h"
#include "backbuffer.h"
#include "label.h"
#include "button.h"
#include "image.h"
#include "logmanager.h"
#include "gameutils.h"
#include "menu.h"
#include "gamestate.h"
#include "resourcemanager.h"
#include "inputhandler.h"
#include "splashscreen.h"
#include "spritemanager.h"
#include "soundmanager.h"

// Library includes:
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>

MenuState::MenuState() 
	: State()
	, m_pMainMenu(0)
{
}

MenuState::~MenuState()
{
	while (!m_splashStack.empty())
	{
		delete m_splashStack.top();
		m_splashStack.pop();
	}

	while (!m_menuStack.empty())
	{
		delete m_menuStack.top();
		m_menuStack.pop();
	}
}

bool
MenuState::Initialise(Sprite* pButton, Sprite* pTitleScreen)
{
	m_type = MainMenu;

	m_pButtonSprite = pButton;
	m_pTitleScreen = pTitleScreen;

	m_pButtonSprite->SetHeight(m_pButtonSprite->GetHeight() * Game::m_screenScaleRatio/24);
	m_pButtonSprite->SetWidth(m_pButtonSprite->GetWidth() * Game::m_screenScaleRatio/24);

	CreateSplash();
	//CreateMainMenu();

	return (true);
}

void
MenuState::Process(float deltaTime)
{
	if (!m_splashStack.empty())
	{
		ProcessSplash(deltaTime);
	}
	else
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
		}
	}
}

void
MenuState::Draw(BackBuffer& backBuffer)
{
	if (!m_splashStack.empty())
	{
		DrawSplash(backBuffer);
	}
	else
	{
		m_menuStack.top()->Draw(backBuffer);
	}
}

void
MenuState::CreateSplash()
{
	//InputEventHandler::GetInstance().Register(COMMAND_QUIT, [this] { ExcapeButtonPressed(); });
	//InputEventHandler::GetInstance().Register(COMMAND_MENU_SELECT, [this] {EnterButtonPressed(); });

	m_pSplash = new SplashScreen();
	m_pSplash->Initialise(ResourceManager::GetInstance().GetSpriteManager().GetSprite(FMODSPRITE));
	m_splashStack.push(m_pSplash);
}

void
MenuState::CreateMainMenu()
{
	m_pMainMenu = new Menu();
	m_pMainMenu->Initialise();

	m_pImage = new Image();
	m_pImage->Initialise(m_pTitleScreen);
	Vector2f vec;
	vec.x = m_pImage->GetDimensions().x;
	vec.y = m_pImage->GetDimensions().y;
	m_pImage->SetDimensions(vec);
	m_pMainMenu->AddChild(m_pImage);

	m_pButton = new Button();
	m_pButton->Initialise(m_pButtonSprite, "Play");
	m_pButton->SetSelected(true);
	m_pButton->SetOnPress([] { Game::GetInstance().AddGameState(); });
	m_pMainMenu->AddButton(m_pButton);

	m_pButton = new Button();
	m_pButton->Initialise(m_pButtonSprite, "Options");
	m_pButton->SetOnPress([&] {CreateOptionsMenu(); });
	m_pMainMenu->AddButton(m_pButton);

	m_pButton = new Button();
	m_pButton->Initialise(m_pButtonSprite, "Credits");
	m_pButton->SetOnPress([&] {CreateCreditsMenu(); });
	m_pMainMenu->AddButton(m_pButton);

	m_pButton = new Button();
	m_pButton->Initialise(m_pButtonSprite, "Quit");
	m_pButton->SetOnPress([] { Game::GetInstance().Quit(); });
	m_pMainMenu->AddButton(m_pButton);

	m_pMainMenu->PositionElements(Game::m_screenDimensions);

	m_menuStack.push(m_pMainMenu);
}

void
MenuState::CreateOptionsMenu()
{
	m_pOptionsMenu = new Menu();
	m_pOptionsMenu->Initialise();

	m_pLabel = new Label();
	m_pLabel->Initialise("Options");
	m_pLabel->SetSize(40);
	m_pLabel->SetAlignment(ALIGN_CENTRE);
	m_pLabel->SetColour(0xFF, 0x00, 0x00);
	m_pOptionsMenu->AddChild(m_pLabel);

	m_pButton = new Button();
	m_pButton->Initialise(m_pButtonSprite, "Audio Options");
	m_pButton->SetSelected(true);
	m_pButton->SetOnPress([&] { CreateAudioOptionsMenu(); });
	m_pOptionsMenu->AddButton(m_pButton);

	m_pButton = new Button();
	m_pButton->Initialise(m_pButtonSprite, "Back");
	m_pButton->SetSelected(false);
	m_pButton->SetOnPress([&] { MenuReturn(); });
	m_pOptionsMenu->AddButton(m_pButton);

	m_pOptionsMenu->PositionElements(Game::m_screenDimensions);

	m_menuStack.push(m_pOptionsMenu);
}

void
MenuState::CreateAudioOptionsMenu()
{
	m_pAudioOptionsMenu = new Menu();
	m_pAudioOptionsMenu->Initialise();

	m_pLabel = new Label();
	m_pLabel->Initialise("Audio Options");
	m_pLabel->SetSize(40);
	m_pLabel->SetAlignment(ALIGN_CENTRE);
	m_pLabel->SetColour(0xFF, 0x00, 0x00);
	m_pAudioOptionsMenu->AddChild(m_pLabel);

	m_pLabel = new Label();
	m_pLabel->Initialise("Audio %");
	m_pLabel->SetSize(40);
	m_pLabel->SetAlignment(ALIGN_CENTRE);
	m_pLabel->SetColour(0x00, 0x00, 0x00);
	m_pAudioOptionsMenu->AddChild(m_pLabel);

	m_pButton = new Button();
	m_pButton->Initialise(m_pButtonSprite, "Toggle Music");
	m_pButton->SetSelected(true);
	m_pButton->SetOnPress([&] { SoundManager::GetInstance().ToggleMusic(); });
	m_pAudioOptionsMenu->AddButton(m_pButton);

	m_pButton = new Button();
	m_pButton->Initialise(m_pButtonSprite, "Increase Volume");
	m_pButton->SetSelected(false);
	m_pButton->SetOnPress([&] { SoundManager::GetInstance().IncreaseVol(); m_pLabel->SetText("Audio up"); });
	m_pAudioOptionsMenu->AddButton(m_pButton);

	m_pButton = new Button();
	m_pButton->Initialise(m_pButtonSprite, "Decrease Volume");
	m_pButton->SetSelected(false);
	m_pButton->SetOnPress([&] { SoundManager::GetInstance().DecreaseVol(); m_pLabel->SetText("Audio down"); });
	m_pAudioOptionsMenu->AddButton(m_pButton);

	m_pButton = new Button();
	m_pButton->Initialise(m_pButtonSprite, "Back");
	m_pButton->SetSelected(false);
	m_pButton->SetOnPress([&] { MenuReturn(); });
	m_pAudioOptionsMenu->AddButton(m_pButton);

	m_pAudioOptionsMenu->PositionElements(Game::m_screenDimensions);

	m_menuStack.push(m_pAudioOptionsMenu);
}

void
MenuState::CreateCreditsMenu()
{
	m_pCreditsMenu = new Menu();
	m_pCreditsMenu->Initialise();

	m_pLabel = new Label();
	m_pLabel->Initialise("Credits");
	m_pLabel->SetSize(40);
	m_pLabel->SetAlignment(ALIGN_CENTRE);
	m_pLabel->SetColour(0xFF, 0x00, 0x00);
	m_pCreditsMenu->AddChild(m_pLabel);

	m_pLabel = new Label();
	m_pLabel->Initialise("Programmer: Danyal Cetin");
	m_pLabel->SetAlignment(ALIGN_CENTRE);
	m_pLabel->SetColour(0x00, 0x00, 0x00);
	m_pCreditsMenu->AddChild(m_pLabel);

	m_pLabel = new Label();
	m_pLabel->Initialise("Artist/Designer: Tammika Cairns");
	m_pLabel->SetAlignment(ALIGN_CENTRE);
	m_pLabel->SetColour(0x00, 0x00, 0x00);
	m_pCreditsMenu->AddChild(m_pLabel);

	m_pButton = new Button();
	m_pButton->Initialise(m_pButtonSprite, "Back");
	m_pButton->SetSelected(true);
	m_pButton->SetOnPress([&] { MenuReturn(); });
	m_pCreditsMenu->AddButton(m_pButton);

	m_pCreditsMenu->PositionElements(Game::m_screenDimensions);

	m_menuStack.push(m_pCreditsMenu);
}

void
MenuState::MenuReturn()
{
	delete m_menuStack.top();
	m_menuStack.pop();

	m_menuStack.top()->SetSelectionCooldown(0.4);
}

void
MenuState::UpButtonPressed()
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
MenuState::DownButtonPressed()
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
MenuState::EnterButtonPressed()
{
	m_menuStack.top()->SetSelectionCooldown(0.4);
	m_menuStack.top()->GetSelectedButton().OnPress();
}

void
MenuState::ProcessSplash(float deltaTime)
{
	if (!m_splashStack.empty())
	{
		if (m_splashStack.top()->Isfinished())
		{
			delete m_splashStack.top();
			m_splashStack.pop();

			if (m_splashStack.empty())
			{
				CreateMainMenu();
			}

		}
		else
		{
			m_splashStack.top()->Process(deltaTime);
		}
	}
}

void
MenuState::DrawSplash(BackBuffer& backBuffer)
{
	m_splashStack.top()->Draw(backBuffer);
}