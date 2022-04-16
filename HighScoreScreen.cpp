#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

#include "GameText.h"
#include "Helpers.h"
#include "HighScoreScreen.h"


HighScoreScreen::HighScoreScreen()
// Setting these variables before the constructor gets called
	: m_canAddNewScore				( false )
	, m_isScoreTableSet				( false )
	, m_isInHighScoreScreen			( false )
	, m_isWarningMessageDisplayed	( false )
	, m_hasBackSpacePressed			( false )
	, m_warningActiveTime			( 0.0f )
	, m_finalScore					( 0 )
	, m_currentAmountOfEntries		( 0 )
	, m_numberOfCharactersEntered	( 0 )
	, m_openedFromState				( OpenedFromStates::MainMenu )
	, m_pWindow						( nullptr )
{
	//Create new text elements to be displayed onto the screen
	m_pEnteredName			= new GameText();
	m_pGameOverPageMessage	= new GameText();
	m_pPressEscape			= new GameText();
	m_pTitleScreen			= new GameText();
	m_pWarningMessage		= new GameText();
	m_pScoresEntryNames		= new GameText[ Settings::HighScoreProperties::c_maxAmountOfEntries ];
	m_pScoresEntryScores	= new GameText[ Settings::HighScoreProperties::c_maxAmountOfEntries ];
}

HighScoreScreen::~HighScoreScreen()
{
	// Delete the pointer texts created by new
	safeDeletePointerArray( m_pScoresEntryScores );
	safeDeletePointerArray( m_pScoresEntryNames );
	safeDeletePointer( m_pWarningMessage );
	safeDeletePointer( m_pTitleScreen );
	safeDeletePointer( m_pPressEscape );
	safeDeletePointer( m_pGameOverPageMessage );
	safeDeletePointer( m_pEnteredName );
}

void HighScoreScreen::initialise()
{
	// Set all the text with necessary properties
	m_pTitleScreen->setGameText( Settings::TextProperties::c_titleScreenTextPosition , Settings::Fonts::c_UIFontAddress , "" , 50 , Settings::Colours::c_white , false );
	m_pGameOverPageMessage->setGameText( Settings::TextProperties::c_gameOverMessageTextPosition , Settings::Fonts::c_UIFontAddress , "" , 30 , Settings::Colours::c_white , false );
	m_pEnteredName->setGameText( Settings::TextProperties::c_nameEnteredTextPosition , Settings::Fonts::c_UIFontAddress , "" , 30 , Settings::Colours::c_white , false );
	m_pWarningMessage->setGameText( Settings::TextProperties::c_warningMessageTextPosition , Settings::Fonts::c_UIFontAddress , "Not Enough Characters To Enter Your Name!" , 30 , Settings::Colours::c_red , true );
	m_pPressEscape->setGameText( Settings::TextProperties::c_pressEscapeTextPosition , Settings::Fonts::c_UIFontAddress , "Press Excape To Return To Main Menu" , 30 , Settings::Colours::c_white , true );

	// Set the score table entry positions
	sf::Vector2f scoreTableEntryPosition = sf::Vector2f( Settings::TextProperties::c_startingScoreTableEntryPosition );

	// Loop through all every entry text and set their positions
	for ( int ScoreTableRow = 0; ScoreTableRow < Settings::HighScoreProperties::c_maxAmountOfEntries; ++ScoreTableRow )
	{
		m_pScoresEntryNames[ ScoreTableRow ].setGameText( scoreTableEntryPosition , Settings::Fonts::c_UIFontAddress , "0. AAAA" , 30 , Settings::Colours::c_white , true );
		m_pScoresEntryScores[ ScoreTableRow ].setGameText( sf::Vector2f( scoreTableEntryPosition.x + Settings::TextProperties::c_scoreEntryOffset , scoreTableEntryPosition.y ) , Settings::Fonts::c_UIFontAddress , "0000" , 30 , Settings::Colours::c_white , true );

		// Increment on the Y axis
		scoreTableEntryPosition.y += Settings::TextProperties::c_entryPositionYIncrementor;

		// Check if i is on the 9th entry, which wil be rank 10
		if ( ScoreTableRow == 9 )
		{
			// Set new position for the entries to be displayed on the other side of the screen
			scoreTableEntryPosition.x +=	Settings::TextProperties::c_entryPositionXIncrementor;
			scoreTableEntryPosition.y =		Settings::TextProperties::c_startingScoreTableEntryPosition.y;
		}
	}

	// Load the high scores
	loadHighScores();
}

void HighScoreScreen::run( sf::RenderWindow* window , OpenedFromStates openedFromState )
{
	// Set the page screen by:
	float deltaTime			= 0; // Create a deltaTime float value
	m_pWindow				= window; // Set window to display the highscore screen
	m_openedFromState		= openedFromState; // Set from where the high score screen was opened from to diplay the correct screen
	m_isInHighScoreScreen	= true;// The player is in the high score screen, so it will activate the loop

	// Set the page screen based on where the it was opened from
	setPageScreen();

	// If the player is still in the high score screen
	while ( m_isInHighScoreScreen == true )
	{
		// Restart the clock every loop so that new time has passed
		m_gameClock.restart();

		// Check for any window events
		handleWindowEvent();

		// Clear the screen
		m_pWindow->clear();

		// Update necessary objects using deltaTime
		update( deltaTime );

		// Render necessary objects
		render();

		// Display it on the window
		m_pWindow->display();

		// Set the delta time that was passed since the gameClock restarted
		deltaTime = m_gameClock.getElapsedTime().asSeconds();
	}
}

void HighScoreScreen::handleWindowEvent()
{
	//This event variable will be used to check for windw events and what keys were pressed for the name
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
			m_isInHighScoreScreen = false;
		}
		
		// Check if the event type is text entered
		if ( event.type == sf::Event::TextEntered )
		{
			// If new score can be added to the high score file
			if ( m_canAddNewScore == true )
			{		
				// Check if the user pressed enter
				if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Enter ) )
				{
					// If the user entered less amount of characters required
					if ( m_numberOfCharactersEntered < Settings::HighScoreProperties::c_characterAmountRequired )
					{
						// Display the warning message
						m_isWarningMessageDisplayed = true;
					}
					// However, if theplayer entered exact amount of characters required
					else if( m_numberOfCharactersEntered == Settings::HighScoreProperties::c_characterAmountRequired )
					{
						// Input the data intothe file
						inputData();
					}
				}
				// Check if the user entered backspace and if backspace has been pressed and it number of characters is more than 0
				else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::BackSpace ) && m_hasBackSpacePressed == false && m_numberOfCharactersEntered > 0 )
				{
					// Backspace has been entered, remove the character entered and decrement the characters entered
					m_hasBackSpacePressed = true;
					m_nameEntered.pop_back();
					m_numberOfCharactersEntered--;
				}
				// If other keys have been entered
				else
				{
					// Check the length of the character is above the required amount
					if ( m_nameEntered.length() >= Settings::HighScoreProperties::c_characterAmountRequired )
					{
						// Erase that character
						m_nameEntered.erase( m_nameEntered.length() );
					}
					// Check if the user has not pressed backspace, enter and space as characters
					else if( event.text.unicode != 8 && event.text.unicode != 13 && event.text.unicode != 32 )
					{
						// Include the that character and increment the amount characters added 
						m_nameEntered += char( event.text.unicode );
						m_numberOfCharactersEntered++;
					}
				}

				// Set the string of what was entered by the user
				m_pEnteredName->setString( m_nameEntered );
			}
			// If the user can't add data
			else
			{
				// If player pressed enter it will send back to main menu
				if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Enter ) )
				{
					m_isInHighScoreScreen = false;
				}
			}
		}
		else
		{
			// Allow backsapce to be entered
			m_hasBackSpacePressed = false;
		}
	}
}

void HighScoreScreen::update( float deltaTime )
{
	// Based on from where the screen was opened
	switch ( m_openedFromState )
	{
		case OpenedFromStates::MainMenu: // From main menu
		{
			// Sort the scores from highest to lowest
			sortScoresFromHighestToLowest();

			// If the user pressed escape key then it will bring them back to the main menu
			if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) )
			{
				m_isInHighScoreScreen = false;
			}
			break;
		}

		case OpenedFromStates::MainGame: // From the main game
		{
			// Display warning message if it's allowed
			displayWarningMessage( deltaTime );
			break;
		}
	}
}

void HighScoreScreen::render()
{
	// Based on from where the screen was opened
	switch ( m_openedFromState )
	{
		case OpenedFromStates::MainMenu: // From main menu
		{
			// Render the title screen, the high score table and press escape text
			m_pTitleScreen->render	( m_pWindow );
			displayHighScores		( m_pWindow );
			m_pPressEscape->render	( m_pWindow );
			break;
		}

		case OpenedFromStates::MainGame: // From the main game
		{
			// Display the title screen, game over message, name entered
			m_pTitleScreen->render			( m_pWindow );
			m_pGameOverPageMessage->render	( m_pWindow );
			m_pEnteredName->render			( m_pWindow );

			// If warning message can be dispalyed, display it
			if ( m_isWarningMessageDisplayed == true )
			{
				m_pWarningMessage->render( m_pWindow );
			}
			break;
		}
	}
}

void HighScoreScreen::setPageScreen()
{
	// Based on from where the screen was opened
	switch ( m_openedFromState )
	{
		case OpenedFromStates::MainMenu: // From main menu
		{
			// Set the string of the title screen and the colour to white
			m_pTitleScreen->setString	( "High Scores Table" );
			m_pTitleScreen->setFillColor( Settings::Colours::c_white );
			break;
		}

		case OpenedFromStates::MainGame: // From the main game
		{
			// Set string of the title screen and set colour to red
			m_pTitleScreen->setString	( "Game Over" );
			m_pTitleScreen->setFillColor( Settings::Colours::c_red );

			// Check if the lowest highscore has been beaten
			if ( m_finalScore > m_highScoreData[ m_currentAmountOfEntries - 1 ].score )
			{
				// Set string of the game over message
				m_pGameOverPageMessage->setString( "Enter Your Name To Save Your Score :\n(Less Than 4 Letters Required)\nPress Enter Key Once Done" );

				// Set these bools that new score can be entered and that high score has been beaten
				m_canAddNewScore = true;
			}
			else // If the highscore has not been beaten
			{
				// Set string of the game over message
				m_pGameOverPageMessage->setString( "Your Score didn't make it to the HighScores\nYou must beat " + m_highScoreData[ m_currentAmountOfEntries - 1 ].name + " that has " + std::to_string( m_highScoreData[ m_currentAmountOfEntries - 1 ].score ) + ".\nPress Enter To Go To Main Menu" );
				m_canAddNewScore = false;
			}
			break;
		}
	}

	// Set origins of the title screen text and the game over message text
	m_pTitleScreen->setOrigin			( m_pTitleScreen->getLocalBounds().width / 2 , m_pTitleScreen->getLocalBounds().height / 2 );
	m_pGameOverPageMessage->setOrigin	( m_pGameOverPageMessage->getLocalBounds().width / 2 , m_pGameOverPageMessage->getLocalBounds().height / 2 );
}

void HighScoreScreen::loadHighScores()
{
	// Open the high scores csv file
	std::ifstream highScoresFile( "csvFiles/HighScores.csv" );

	// Loop through the max amount of entries, which is are the rows
	for ( int fileRowID = 0; fileRowID < Settings::HighScoreProperties::c_maxAmountOfEntries; ++fileRowID )
	{
		// Create a string for file row and use get line to get whole row
		std::string fileRow;
		std::getline( highScoresFile , fileRow );

		// Create an instance of that row, to be split into elements
		std::stringstream stringStreamMapRow( fileRow );

		// Loop through the amount of types of data stored
		for ( int fileColumnID = 0; fileColumnID < Settings::HighScoreProperties::c_amountOfTypesOfDataStored; ++fileColumnID )
		{
			// Create a string for file element ans using getline function to split the row by commas
			std::string fileElement;
			std::getline( stringStreamMapRow , fileElement , ',' );

			// Create instance of the file element to be used as a converter
			std::stringstream converter( fileElement );

			// Check if file element is of the name is not empty
			if ( fileElement != "" )
			{
				// Switch between the data type is on
				switch ( fileColumnID )
				{
					case 0: // The sname (String)
					{
						converter >> m_highScoreData[ fileRowID ].name; // Store it in the name field
						break;
					}

					case 1: // The score (Int)
					{
						converter >> m_highScoreData[ fileRowID ].score; // Store it in the score field
						m_currentAmountOfEntries++; // Increment the amount of entries
						break;
					}
				}
			}
		}
	}

	// Sort all the entries to be able to display them in their right places
	sortScoresFromHighestToLowest();
}

void HighScoreScreen::inputData()
{
	// Create a bool to check if data has been added already
	bool hasDataBeenAdded = false;

	// Loop through the high score data struct 
	for ( int entryID = 0; entryID < Settings::HighScoreProperties::c_maxAmountOfEntries; ++entryID )
	{
		// Check if the name of the current entry is empty and data has not been added
		if ( m_highScoreData[ entryID ].name == "" && hasDataBeenAdded == false )
		{
			// Set the name that has been entered and the score into the data struct and so data has beeen added
			m_highScoreData[ entryID ].name		= m_pEnteredName->getString();
			m_highScoreData[ entryID ].score	= m_finalScore;
			hasDataBeenAdded = true;
		}
		// Check if new score can be added and the loop is on the last entry
		else if ( m_canAddNewScore == true && entryID == Settings::HighScoreProperties::c_maxAmountOfEntries - 1 )
		{
			// Set the name that has been entered and the score into the data struct and so data has beeen added
			m_highScoreData[ entryID ].name		= m_pEnteredName->getString();
			m_highScoreData[ entryID ].score	= m_finalScore;
			hasDataBeenAdded = true;
		}

		// If data has been added break the loop, which will stop it
		if ( hasDataBeenAdded == true )
		{
			break;
		}
	}

	// Open the high scores file
	std::ofstream highScoresFile;
	highScoresFile.open( "csvFiles/HighScores.csv" );

	// Loop through the high score data struct
	for ( int entryID = 0; entryID < Settings::HighScoreProperties::c_maxAmountOfEntries; ++entryID )
	{
		// Check if the high score entry name is not empty
		if ( m_highScoreData[ entryID ].name != "" )
		{
			// Added the name and highscore to the csv file
			highScoresFile << m_highScoreData[ entryID ].name << "," << m_highScoreData[ entryID ].score << "," << '\n';
		}
		else
		{
			// Break the loop if there is an empty name
			break;
		}
	}

	// Close the file
	highScoresFile.close();

	// Sort all of the scores so that new the lowest entry can be checked
	sortScoresFromHighestToLowest();

	// Reset the values and send the user to the main menu
	resetValues();
	m_isInHighScoreScreen = false;
}

void HighScoreScreen::displayHighScores( sf::RenderTarget* targetWindow )
{
	// Check if the score table is set
	if ( m_isScoreTableSet == false )
	{
		// Create an int for the rank
		int rankNumber = 1;

		// Sort through the through the scores from highest to lowest
		sortScoresFromHighestToLowest();

		// Loop through the high score data struct
		for ( int i = 0; i < Settings::HighScoreProperties::c_maxAmountOfEntries; ++i )
		{
			// Check if the name in the data is not empty
			if ( m_highScoreData[ i ].name != "" )
			{
				// Set the rank followed by the name and the score to display as text
				m_pScoresEntryNames[ i ].setString	( std::to_string( rankNumber ) + ". " + m_highScoreData[ i ].name );
				m_pScoresEntryScores[ i ].setString	( std::to_string( m_highScoreData[ i ].score ) );

				// Increment the rank number
				rankNumber++;
			}
		}

		// After going through the high score struct, the score table is eet
		m_isScoreTableSet = true;
	}

	// Loop through all current amount of enteries available
	for ( int i = 0; i < m_currentAmountOfEntries; ++i )
	{
		// Display the the names and scores
		m_pScoresEntryNames[ i ].render	( targetWindow );
		m_pScoresEntryScores[ i ].render( targetWindow );
	}
}

void HighScoreScreen::sortScoresFromHighestToLowest()
{
	bool swapped	= true; // Create a bool to check if the entry has been swapped
	int entries		= m_currentAmountOfEntries; // Create an int that will be used to through entries that haven't been swapped

	// While the entry has been swapped
	while ( swapped == true)
	{
		// The entry has not been swapped
		swapped = false;

		// Go through all entries
		for ( int entryID = 0; entryID < ( entries - 1 ); ++entryID )
		{
			// Check if the entry is smaller than the one next  in the index
			if ( m_highScoreData[ entryID ].score < m_highScoreData[ entryID + 1 ].score )
			{
				// Store the smaller entry name and score in temperory variables
				std::string temporaryName				= m_highScoreData[ entryID ].name;
				int temporaryScore						= m_highScoreData[ entryID ].score;

				// Swap the bigger entry to that position, where the smallest one was
				m_highScoreData[ entryID ].name			= m_highScoreData[ entryID + 1 ].name;
				m_highScoreData[ entryID ].score		= m_highScoreData[ entryID + 1 ].score;

				// Put the smaller entry to the position where the bigger was
				m_highScoreData[ entryID + 1 ].name		= temporaryName;
				m_highScoreData[ entryID + 1 ].score	= temporaryScore;

				// Swapped has happened
				swapped = true;
			}
		}

		// Decrement the last entry swap with, so it guarantees that the smaller score entry is at the bottom, so it won't check it again
		entries--;
	}
}

void HighScoreScreen::resetValues()
{
	// Reset these values until the player will re-enter the scores
	m_canAddNewScore			= false;
	m_numberOfCharactersEntered = 0;
	m_nameEntered				= "";
}

void HighScoreScreen::displayWarningMessage( float deltaTime )
{
	// Check if the warning is displayed
	if ( m_isWarningMessageDisplayed == true )
	{
		// Increment the time to display the warning message
		m_warningActiveTime += deltaTime;

		// Check if the warning time is above the max display time
		if ( m_warningActiveTime > Settings::HighScoreProperties::c_maxTimeDisplayingWarningMessage )
		{
			// Reset the warning active time and hide the text from the screen
			m_warningActiveTime			= 0.0f;
			m_isWarningMessageDisplayed = false;
		}
	}
}

void HighScoreScreen::setIsScoreTableSet( bool isScoreTableSet )	{ m_isScoreTableSet = isScoreTableSet; }

void HighScoreScreen::setFinalScore( int finalscore )				{ m_finalScore = finalscore; }
