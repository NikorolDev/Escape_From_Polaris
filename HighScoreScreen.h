#ifndef HIGHSCORESCREEN_H
#define HIGHSCORESCREEN_H

#include <fstream>
#include <iostream>
#include <sstream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "Settings.h"

// Forward class declarations of game text
class GameText;

// Data struct of high scores
struct HighScore
{
	std::string name; // The name of the player
	int			score; // The score they got at the end
};

// The states of where the high score screen was opened from
enum class OpenedFromStates
{
	MainMenu, MainGame
};

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: EnemyBase
// Classes Inherited	: SpriteObject
// Purpose				: To handle every single enemy in this base class, such as health handling and moving to formaitons
//-------------------------------------------------------------------------------------------------------------------------
class HighScoreScreen
{
private:
#pragma region private variables
	bool				m_canAddNewScore; // This will check if the player can add new scores, which will set a different screens based on it
	bool				m_isScoreTableSet; // This will check if the high score table has been set 
	bool				m_isInHighScoreScreen; // This will be used in the while to state that the player is in the high score screen
	bool				m_isWarningMessageDisplayed; // This will allow the warning message to be displayed
	bool				m_hasBackSpacePressed; // This is to check if backspace has been pressed so that there is a released key effect

	float				m_warningActiveTime; // The time that warning time has been displayed

	int					m_finalScore; // The final score that the player got after dying
	int					m_currentAmountOfEntries; // The ccurent amount of enteries in the csv file, so it can be used to fill any emtpy entries if needed
	int					m_numberOfCharactersEntered; // The number of characters entered when entering a name

	HighScore			m_highScoreData[ Settings::HighScoreProperties::c_maxAmountOfEntries ]; // An array of the high score data, which is the amount of entries
	OpenedFromStates	m_openedFromState; // The state that high score screen was opened from

	GameText*			m_pEnteredName; // Text that will diplay what name the player entered per character selected
	GameText*			m_pGameOverPageMessage; // The game over page message, which will be to beat high score or to enter one
	GameText*			m_pPressEscape; // The message for user to get back to the main menu
	GameText*			m_pTitleScreen; // The title of the screen
	GameText*			m_pScoresEntryNames; // The entry name text that is linked to the score
	GameText*			m_pScoresEntryScores; // The entry score that that is linked to the name
	GameText*			m_pWarningMessage; // Warning meesage that player included not enough amount of characters

	std::string			m_nameEntered; // The name that was entered by the player

	sf::Clock			m_gameClock; // The system clock needed to get delta time
	sf::RenderWindow*	m_pWindow; // The window that will display the high score screen

#pragma endregion

#pragma region private function
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: handleWindowEvent()
	// Parameters		: None
	// Purpose			: To handle events, for example when window closes and when the player types something to enter 
	//					,	their name for the high scores
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void handleWindowEvent();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: update()
	// Parameters		: deltaTime - This will be used to time how long the warning meesage was on for
	// Purpose			: This will update all necessary UI based on where this screen was accessed from
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void update( float deltaTime );

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: render()
	// Parameters		: None
	// Purpose			: This will render all necessary UI based on where this screen was accessed from
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void render();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: setPageScreen()
	// Parameters		: None
	// Purpose			: This will set the high score screen based on where it was opened from
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void setPageScreen();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: loadHighScores()
	// Parameters		: None
	// Purpose			: This will load the high scores from the highscore.csv file
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void loadHighScores();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: inputData()
	// Parameters		: None
	// Purpose			: This will input all of the data into the file
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void inputData();
	
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: displayHighScores( sf::RenderTarget* targetWindow )
	// Parameters		: targetWindow - the window to render object to
	// Purpose			: This will display all of the names followed by high scores
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void displayHighScores( sf::RenderTarget* targetWindow );

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: sortScoresFromHighestToLowest()
	// Parameters		: None
	// Purpose			: This will sort the scores from highest to lowest, which will be good setting the scores
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void sortScoresFromHighestToLowest();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: resetValues()
	// Parameters		: None
	// Purpose			: This will reset all of the values when exiting the high scores screen
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void resetValues();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: displayWarningMessage(float deltaTime)
	// Parameters		: deltaTime - This will be needed to increment the time to keep the warning message displayed
	// Purpose			: This will allow the warning message to display when thplayer enteres less amount of characters
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void displayWarningMessage( float deltaTime );

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: HighScoreScreen()
	// Parameters		: None
	// Notes			: This will initialise private variables and create UI objects, which will be mainly text elements
	//---------------------------------------------------------------------------------------------------------------------
	HighScoreScreen();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: HighScoreScreen()
	// Parameters		: None
	// Notes			: This destructor will delete itself and delete the UI objects that were in created as new
	//---------------------------------------------------------------------------------------------------------------------
	~HighScoreScreen(); 

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: initialise()
	// Parameters		: None
	// Purpose			: This initialise function will set all of text elements and load the high scores from the csv file
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void initialise();

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: run(sf::RenderWindow* window , OpenedFromStates openedFromState)
	// Parameters		: window - The window that will display the scores
	//					, openedFromState - the state that the high scores screen was opened from
	// Purpose			: This will run the high score screen based on where it was opened from
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void run( sf::RenderWindow* window , OpenedFromStates openedFromState );

#pragma endregion

#pragma region getters and setters
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setIsScoreTableSet(bool isScoreTableSet)
	// Parameters		: isScoreTableSet - To set if the score table has been set
	// Purpose			: This will mainly set the bool false when exiting the high scores screen from the main menu
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setIsScoreTableSet( bool isScoreTableSet );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setFinalScore(int finalscore)
	// Parameters		: finalscore - The final scores that the player got at the end
	// Purpose			: This will set the final score that player to checked whether it can be put into the highscores or 
	//					,	not
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setFinalScore( int finalscore );

#pragma endregion

};

#endif // !HIGHSCORESCREEN_H
