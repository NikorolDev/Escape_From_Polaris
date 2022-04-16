#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics/RenderWindow.hpp>

// Forward class declarations
class AudioManager;
class GameText;
class HighScoreScreen;
class MainGame;
class SpriteObject;
class TextureManager;

// Enum for the options in the main menu
enum class MainMenuOptions{MainMenu , Play , Help , HighScores, Exit};

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: MainMenu
// Classes Inherited	: None
// Purpose				: To handle how the main menu will run based on updating and drawing objects
//-------------------------------------------------------------------------------------------------------------------------
class MainMenu
{
private:
#pragma region private variables
	bool				m_hasSKeyButtonPressed; // This will check if the S key has been pressed
	bool				m_hasSpaceKeyButtonPressed; // This will check if the Space key has been pressed
	bool				m_hasWKeyButtonPressed; // This will check if the W key has been pressed

	int					m_selectedMenuOptionID; // The selected menu option ID, for setting the enum menu option

	MainMenuOptions		m_selectedMenuOption; // The selected menu option 

	AudioManager*		m_pAudioManager;
	GameText*			m_pGameTitle; // Title of the Game
	GameText*			m_pMenuButtons; // The array of menu buttons as text
	GameText*			m_pMenuTitle; // Menu titles texts
	GameText*			m_pPressEscape; // Press to escape text
	HighScoreScreen*	m_pHighScoreScreen; // The high score screen that will run when accessing the score board
	MainGame*			m_pMainGame; // The main game to run when the user wants to play game
	SpriteObject*		m_pHelpScreen; // The image of the help screen

	sf::RenderWindow*	m_pWindow; // The game window that will display our game

#pragma endregion

#pragma region private function
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: handleWindowEvent()
	// Parameters		: None
	// Purpose			: To handle window events, for example when window closes
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void handleWindowEvent();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: update(float deltaTime)
	// Parameters		: deltaTime - This will be used to make our movements smoother and frame rate independent
	// Purpose			: This will update all necessary objects as the game is running
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void update();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: render()
	// Parameters		: None
	// Purpose			: This will render all necessary objects as the game is running
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void render();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: mainMenuControls()
	// Parameters		: None
	// Purpose			: This will check for input to navigate around the main menu
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void mainMenuControls();

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: MainMenu()
	// Parameters		: None
	// Notes			: This will initialise private variables and initialise pointers
	//---------------------------------------------------------------------------------------------------------------------
	MainMenu();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: MainGame()
	// Parameters		: None
	// Notes			: This destructor will delete all the pointers made
	//---------------------------------------------------------------------------------------------------------------------
	~MainMenu();

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: initialise(TextureManager* pTextureManager , MainGame* pMainGame , HighScoreScreen* pHighScoreScreen)
	// Parameters		: pAudioManager - to play the main menu music
	//					, pTextureManager - to set the texture of the help screen
	//					, pMainGame - to be able to run the game from the main menu
	//					, pHighScoreScreen - to be able to run the high score screen from the main menu
	// Purpose			: This initialise function will set the pointers needed to run other states of the game and set 
	//					,	texture to the help screen
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void initialise( AudioManager* pAudioManager , TextureManager* pTextureManager , MainGame* pMainGame , HighScoreScreen* pHighScoreScreen );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: run(sf::RenderWindow* window)
	// Parameters		: window - The window that will display the scores
	// Purpose			: This will run the main menu screen by updating and rendering as long as the user doesn't exit the 
	//					,	game
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void run( sf::RenderWindow* window );

#pragma endregion

};

#endif // !MAINMENU_H
