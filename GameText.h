#ifndef GAMETEXT_H
#define GAMETEXT_H

#include <SFML/Graphics/Text.hpp>

#include "Object.h"

// Forward declarations of the player
class Player;

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: GameText
// Classes Inherited	: Object and Text
// Purpose				: To handle the game text, like what is displayed and how its displayed
//-------------------------------------------------------------------------------------------------------------------------
class GameText : public Object, public sf::Text
{
private:
#pragma region private variables
	sf::Font m_font; // The font that will be used load and to use for that text

#pragma endregion

#pragma region private function
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: loadFont(const sf::String& fontStyle)
	// Parameters		: fontStyle - The font file that will be loaded to the game
	// Purpose			: This will load the font from the file address that's been passed through
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void loadFont( const sf::String& fontStyle );

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: GameText()
	// Parameters		: None
	// Notes			: As this is a default constructor it will initialise nothing as the font has its own constructor
	//---------------------------------------------------------------------------------------------------------------------
	GameText();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: GameText()
	// Parameters		: None
	// Notes			: This destructor will delete itself and as it is virtual it will delete the child classes as well
	//---------------------------------------------------------------------------------------------------------------------
	virtual ~GameText();

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: initialise(Player* m_pPlayer)
	// Parameters		: pPlayer - passed through player that will be stored in child classes that need to update the text
	// Purpose			: This initialise function will only be used for child classes that need the player passed through
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void initialise( Player* m_pPlayer ) {};

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: render(sf::RenderTarget* targetWindow)
	// Parameters		: targetWindow - the window to render object to
	// Purpose			: To render the text onto the screen
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void render( sf::RenderTarget* targetWindow );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setGameText(const sf::Vector2f& position , const sf::String& fontStyle , const sf::String& text , const int fontSize , const sf::Color& textColour , bool setMiddleOrigin)
	// Parameters		: position - The position of the text
	//					, fontStyle - The style of the font
	//					, text - The text to be displayed
	//					, fontSize - the size of the font 
	//					, textColour - the colour of the text
	//					, setMiddleOrigin - Should the text origin be set to the middle
	// Purpose			: This will set game text using these properties
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setGameText( const sf::Vector2f& position , const sf::String& fontStyle , const sf::String& text , const int fontSize , const sf::Color& textColour , bool setMiddleOrigin );

#pragma endregion

};

#endif // !GAMETEXT_H

