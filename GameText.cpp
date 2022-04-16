#include <string.h>

#include "GameText.h"
#include "Helpers.h"

GameText::GameText()
{
}

GameText::~GameText()
{
}

void GameText::render( sf::RenderTarget* targetWindow )
{
	// Render the text to the screen
	targetWindow->draw( *this );
}

void GameText::setGameText( const sf::Vector2f& position , const sf::String& fontStyle , const sf::String& text , const int fontSize , const sf::Color& textColour , bool setMiddleOrigin )
{
	// Load the font, set position, set font size, set the text and fill colour
	loadFont( fontStyle );
	setPosition( position );
	setCharacterSize( fontSize );
	setString( text );
	setFillColor( textColour );

	// Check if the text should set its origin to the middle
	if ( setMiddleOrigin == true )
	{
		// Set the origin based on the text width and height
		setOrigin( getLocalBounds().width / 2 , getLocalBounds().height / 2 );
	}
}

void GameText::loadFont( const sf::String& fontStyle )
{
	// This bool will set if the font has loaded in or not
	bool loadedSuccessfully = m_font.loadFromFile( fontStyle );
	
	// Stop the game if font was not able to load
	ASSERT( loadedSuccessfully );

	// Set the font
	setFont( m_font );
}
