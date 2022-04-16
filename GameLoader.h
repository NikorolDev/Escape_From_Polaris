#ifndef GAMELOADER_H
#define GAMELOADER_H

#include <SFML/Graphics/RenderWindow.hpp>

// Forward class declarations of these classes
class AudioManager;
class HighScoreScreen;
class MainGame;
class MainMenu;
class TextureManager;

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: GameLoader
// Classes Inherited	: None
// Purpose				: To load everything into the game before running and delete everything after closing the game
//-------------------------------------------------------------------------------------------------------------------------
class GameLoader
{
private:
#pragma region private variables
	AudioManager*		m_pAudioManager; // To load sounds and play them
	HighScoreScreen*	m_pHighScoreScreen; // The high score screen in the game
	MainGame*			m_pMainGame; // The game that the player will play on
	MainMenu*			m_pMainMenu; // The main menu of the game to navigate around different states and screens
	TextureManager*		m_pTextureManager; /// To load every texture into the game

	sf::RenderWindow	m_window; // The game window that will display our game

#pragma endregion

#pragma region private functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: loadAudio()
	// Parameters		: None
	// Purpose			: This will load every audio file into the audio manager, so that it can be retrieved to play 
	//					,	sounds
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void loadAudio();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: loadTextures()
	// Parameters		: None
	// Purpose			: This will load every texture into the texture manager, so that it can be retrieved to set 
	//					,	textures onto sprites
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void loadTextures();

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: GameLoader()
	// Parameters		: None
	// Notes			: This constructor will initialise all of the states in the game, which are game, main menu and 
	//					,	highscore screen
	//---------------------------------------------------------------------------------------------------------------------
	GameLoader();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: GameLoader()
	// Parameters		: None
	// Notes			: This destructor will delete every state, which means it will delete everything closing the game 
	//					,	with no memory leaks
	//---------------------------------------------------------------------------------------------------------------------
	~GameLoader();

#pragma endregion
	
#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: initialise()
	// Parameters		: None
	// Purpose			: This will initialise the whole game, by calling state initialisers and run the main menu first
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void initialise();

#pragma endregion
};

#endif // !GAMELOADER_H
