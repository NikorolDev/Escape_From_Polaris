#include "LivesText.h"
#include "Player.h"
#include "Settings.h"

LivesText::LivesText()
// Setting the player to null pointer
	: m_pPlayer		( nullptr )
{
	// Set the game text
	setGameText( sf::Vector2f( 50 , 735 ) , Settings::Fonts::c_UIFontAddress , "Lives: 0" , 20 , sf::Color( 255 , 255 , 255 , 255 ) , true );
}

void LivesText::initialise( Player* pPlayer )
{
	// Set the player
	m_pPlayer = pPlayer;
}

void LivesText::render( sf::RenderTarget* targetWindow )
{
	// Create a string to display the score and convert player score into text, then set the string
	std::string lives = "Lives: " + std::to_string( m_pPlayer->getLives() );
	setString( lives );

	// Redner the text
	GameText::render( targetWindow );
}
