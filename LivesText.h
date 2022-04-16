#ifndef LIVERTEXT_H
#define LIVERTEXT_H

#include "GameText.h"

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: ScoresText
// Classes Inherited	: GameText
// Purpose				: To handle the player's lives displayed
//-------------------------------------------------------------------------------------------------------------------------
class LivesText :public GameText
{
#pragma region private variables
	Player* m_pPlayer; // The player pointer to get the score

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: ScoresText()
	// Parameters		: None
	// Notes			: As this constructor will set the game text
	//---------------------------------------------------------------------------------------------------------------------
	LivesText();

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: initialise(Player* m_pPlayer)
	// Parameters		: pPlayer - passed through player that will be used get the score
	// Purpose			: This initialise function will only be set the player as data to get the lives
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void initialise( Player* pPlayer );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: render(sf::RenderTarget* targetWindow)
	// Parameters		: targetWindow - the window to render object to
	// Purpose			: To render the lives onto the screen
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void render( sf::RenderTarget* targetWindow ) override;

#pragma endregion

};

#endif // !LIVERTEXT_H
