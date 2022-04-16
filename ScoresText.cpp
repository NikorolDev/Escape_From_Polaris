#include "Player.h"
#include "ScoresText.h"
#include "Settings.h"

ScoresText::ScoresText()
// Setting the player to null pointer
	: m_pPlayer		( nullptr )
{
	// Set the game text
	setGameText( Settings::TextProperties::c_scoreTextPosition , Settings::Fonts::c_UIFontAddress , "Score: 0000" , 20 , Settings::Colours::c_white, true );
}

void ScoresText::initialise( Player* pPlayer )
{
	// Set the player
	m_pPlayer = pPlayer;
}

void ScoresText::render( sf::RenderTarget* targetWindow )
{
	// Create a string to display the score and convert player score into text, then set the string
	std::string score = "Score: " + std::to_string( m_pPlayer->getScore() );
	setString( score );

	// Redner the text
	GameText::render( targetWindow );
}
