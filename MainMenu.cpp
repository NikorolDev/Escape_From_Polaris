#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "AudioManager.h"
#include "GameText.h"
#include "Helpers.h"
#include "HighScoreScreen.h"
#include "MainGame.h"
#include "MainMenu.h"
#include "Settings.h"
#include "SpriteObject.h"
#include "TextureManager.h"

MainMenu::MainMenu()
// Setting these variables before the constructor gets called
	: m_hasSKeyButtonPressed		( false )
	, m_hasSpaceKeyButtonPressed	( false )
	, m_hasWKeyButtonPressed		( false )
	, m_selectedMenuOptionID		( 0 )
	, m_selectedMenuOption			( MainMenuOptions::MainMenu )
	, m_pAudioManager				( nullptr )
	, m_pHighScoreScreen			( nullptr )
	, m_pMainGame					( nullptr )
	, m_pWindow						( nullptr )
{
	// Create new texts for screen titles and buttons
	m_pGameTitle = new GameText();
	m_pMenuTitle = new GameText();
	m_pPressEscape = new GameText();
	m_pMenuButtons = new GameText[ Settings::MainMenuProperties::c_maxAmountOfButtons ];

	// Create a new image for the help screen
	m_pHelpScreen = new SpriteObject();
}

MainMenu::~MainMenu()
{
	// Delete each pointer that was created as new in this class
	safeDeletePointerArray( m_pMenuButtons );
	safeDeletePointer( m_pPressEscape );
	safeDeletePointer( m_pMenuTitle );
	safeDeletePointer( m_pHelpScreen );
	safeDeletePointer( m_pGameTitle );
}

void MainMenu::initialise( AudioManager* pAudioManager , TextureManager* pTextureManager , MainGame* pMainGame , HighScoreScreen* pHighScoreScreen )
{
	// set the main game, so it can urun the game
	m_pAudioManager		= pAudioManager;
	m_pMainGame			= pMainGame;
	m_pHighScoreScreen	= pHighScoreScreen;

	// Set the text properties for the Game Title, menu titles, press to escape, and menu buttons
	m_pGameTitle->setGameText( Settings::TextProperties::c_titleScreenTextPosition , Settings::Fonts::c_UIFontAddress , "Escape From Polaris" , 50 , Settings::Colours::c_white , true );
	m_pMenuTitle->setGameText( sf::Vector2f( Settings::TextProperties::c_titleScreenTextPosition ) , Settings::Fonts::c_UIFontAddress , "Help" , 50 , Settings::Colours::c_white , true );
	m_pPressEscape->setGameText( Settings::TextProperties::c_pressEscapeTextPosition , Settings::Fonts::c_UIFontAddress , "Press Excape To Return To Main Menu" , 30 , Settings::Colours::c_white , true );

	m_pMenuButtons[ 0 ].setGameText( sf::Vector2f( 400 , 300 ) , Settings::Fonts::c_UIFontAddress , "Play" , 30 , Settings::Colours::c_white , true );
	m_pMenuButtons[ 1 ].setGameText( sf::Vector2f( 400 , 350 ) , Settings::Fonts::c_UIFontAddress , "Help" , 30 , Settings::Colours::c_white , true );
	m_pMenuButtons[ 2 ].setGameText( sf::Vector2f( 400 , 400 ) , Settings::Fonts::c_UIFontAddress , "High Scores" , 30 , Settings::Colours::c_white , true );
	m_pMenuButtons[ 3 ].setGameText( sf::Vector2f( 400 , 450 ) , Settings::Fonts::c_UIFontAddress , "Exit" , 30 , Settings::Colours::c_white , true );

	// Load texture of the help screen and set its position
	m_pHelpScreen->loadSpriteTexture( pTextureManager->getTexture( GameTextures::HelpScreen ) , false );
	m_pHelpScreen->setPosition( Settings::MainMenuProperties::c_helpScreenPosition );
}

void MainMenu::run( sf::RenderWindow* window )
{
	// Play the music. which will be set to be looping, until the game closes
	m_pAudioManager->playAudio( GameSounds::Music );

	// Create the game window using the set window width and height
	m_pWindow = window;

	while ( m_pWindow->isOpen() )
	{
		// Check for any window events
		handleWindowEvent();

		// Clear the screen
		m_pWindow->clear();

		// Update necessary objects using deltaTime
		update();

		// Render necessary objects
		render();

		// Display it on the window
		m_pWindow->display();
	}
}

void MainMenu::handleWindowEvent()
{
	//This event variable will be used to check for windw events
	sf::Event event;

	// This while loop will check if any events have been triggered.
	// If no window events have been triggered, keep the game running
	while ( m_pWindow->pollEvent( event ) )
	{
		// Check if the event was to close the game
		if ( event.type == sf::Event::Closed )
		{
			// Close the window
			m_pWindow->close();
		}
	}
}

void MainMenu::update()
{
	// Switch based on menu option selected
	switch ( m_selectedMenuOption )
	{
		case MainMenuOptions::MainMenu: // If the player selected the main menu
		{
			// Use the main menu controls to navigate around the main menu
			mainMenuControls();
			break;
		}

		case MainMenuOptions::Play: // If the player selected to play the game
		{
			// Start running the game itself
			m_pMainGame->run( m_pWindow );

			// Once the game has stopped running return them to the Game Over screen
			m_selectedMenuOption = MainMenuOptions::MainMenu;
			break;
		}

		case MainMenuOptions::Help: // If the player chose to go to help screen
		{
			// If pressed the esc key, it will bring them back to the main menu screen
			if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
			{
				m_selectedMenuOption = MainMenuOptions::MainMenu;
			}
			break;
		}

		case MainMenuOptions::HighScores: // If the player chose to go to highscores screen
		{
			// Run the high score screen 
			m_pHighScoreScreen->run( m_pWindow , OpenedFromStates::MainMenu );

			// Once exited the high score screen, go back to main menu and allow the score table to reset
			m_selectedMenuOption = MainMenuOptions::MainMenu;
			m_pHighScoreScreen->setIsScoreTableSet( false );
			break;
		}

		case MainMenuOptions::Exit: // If the player chose to go to exit the game
		{
			// Then close the game
			m_pWindow->close();
			break;
		}
	}
}

void MainMenu::render()
{
	// Switch based on menu option selected
	switch ( m_selectedMenuOption )
	{
		case MainMenuOptions::MainMenu: // If the player selected the main menu
		{
			// Render the game title and menu buttons
			m_pGameTitle->render( m_pWindow );

			// Loop through all buttons and render them
			for ( int buttonID = 0; buttonID < Settings::MainMenuProperties::c_maxAmountOfButtons; ++buttonID )
			{
				m_pMenuButtons[ buttonID ].render( m_pWindow );
			}
			break;
		}

		case MainMenuOptions::Help: // If the player selected the help screen
		{
			// Render the help menu title, help screen, and press escape text
			m_pMenuTitle->render	( m_pWindow );
			m_pWindow->draw			( *m_pHelpScreen );
			m_pPressEscape->render	( m_pWindow );
			break;
		}
	}
}

void MainMenu::mainMenuControls()
{
	// In order to navigate around the main menu
	// When the user presses W key
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
	{
		// Check if the W key has not been pressed yet
		if ( m_hasWKeyButtonPressed == false )
		{
			// W key key has been pressed, so it will make a relase effect
			m_hasWKeyButtonPressed = true;

			// Check if the selected menu option ID is above 0
			if ( m_selectedMenuOptionID > 0 )
			{
				// Colour the previous button  in white and decrement the slected menu option ID
				m_pMenuButtons[ m_selectedMenuOptionID ].setFillColor( sf::Color( Settings::Colours::c_white ) );
				m_selectedMenuOptionID--;
			}
		}
	}
	else
	{
		// Allow the W key to be pressed
		m_hasWKeyButtonPressed = false;
	}

	// When the user presses S key
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
	{
		// Check if the S key has not been pressed yet
		if ( m_hasSKeyButtonPressed == false )
		{
			// S key key has been pressed, so it will make a relase effect
			m_hasSKeyButtonPressed = true;

			// Check if the selected menu option ID is below the last button, by getting the last index
			if ( m_selectedMenuOptionID < Settings::MainMenuProperties::c_maxAmountOfButtons - 1 )
			{
				// Colour the previous button  in white and decrement the slected menu option ID
				m_pMenuButtons[ m_selectedMenuOptionID ].setFillColor( sf::Color( Settings::Colours::c_white ) );
				m_selectedMenuOptionID++;
			}
		}
	}		
	else
	{
		// Allow the S key to be pressed
		m_hasSKeyButtonPressed = false;
	}

	// Colour the button the user is currently on to green
	m_pMenuButtons[ m_selectedMenuOptionID ].setFillColor( sf::Color( Settings::Colours::c_green ) );

	// When the user presses Space bar
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) )
	{
		// Check if the Space bar has not been pressed yet
		if ( m_hasSpaceKeyButtonPressed == false )
		{
			// Space bar key has been pressed, so it will make a relase effect
			m_hasSKeyButtonPressed = true;

			// Switch based on the selected menu option
			switch ( m_selectedMenuOptionID )
			{
				// For all cases it will set the menu option selected enum, which will
				case 0: // Run the main game
				{
					m_selectedMenuOption = MainMenuOptions::Play;
					break;
				}

				case 1: // Take the user to the help screen
				{
					m_selectedMenuOption = MainMenuOptions::Help;
					break;
				}

				case 2: // Take the user to the high scores screen
				{
					m_selectedMenuOption = MainMenuOptions::HighScores;
					break;
				}

				case 3: // close the game
				{
					m_selectedMenuOption = MainMenuOptions::Exit;
					break;
				}
			}
		}
	}
	else
	{
		// Allow the Space bar to be pressed
		m_hasSpaceKeyButtonPressed = false;
	}
}
