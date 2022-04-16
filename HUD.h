#ifndef HUD_H
#define HUD_H

#include "Object.h"

// Forward class declarations
class LivesText;
class Player;
class PlayerHealthBar;
class PowerUpBar;
class ScoresText;
class TextureManager;

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: HUD
// Classes Inherited	: Object
// Purpose				: To handle every single HUD element in the game
//-------------------------------------------------------------------------------------------------------------------------
class HUD : public Object
{
private:
#pragma region private variables
	LivesText*			m_pLivesText; // The lives text to be updated and displayed
	Player*				m_pPlayer; // The player that wil get the scores and lives
	PlayerHealthBar*	m_pPlayerHealthBar; // The health bar to be updated and rendered
	PowerUpBar*			m_pPowerUpBar; // The power up bar to be updated amd rendered
	ScoresText*			m_pScoreText; // The scores text to be updated and diplayed

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: HUD()
	// Parameters		: None
	// Notes			: This construcotr will create new texts and progression bars for the HUD
	//---------------------------------------------------------------------------------------------------------------------
	HUD();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: HUD()
	// Parameters		: None
	// Notes			: This destructor will delete itself and delete the text objects and progression bars that created
	//					,	as new
	//---------------------------------------------------------------------------------------------------------------------
	~HUD();

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: initialise(Player* pPlayer , TextureManager* pTextureManager)
	// Parameters		: pPlayer - passed through player that will be stored to pass the data that needs to be displayed 
	//					,	and preocessed
	//					, pTextureManager - to pass texture manager, which will set textures of the progression bars
	// Purpose			: This initialise function will initialise the HUD to be ready to display the information on to the
	//					,	screen
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void initialise( Player* pPlayer , TextureManager* pTextureManager );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: update()
	// Parameters		: None
	// Purpose			: This update function will update the progression bars using player values
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void update();

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: render(sf::RenderTarget* targetWindow)
	// Parameters		: targetWindow - the window to render object to
	// Purpose			: To render the every HUD element in the game
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void render( sf::RenderTarget* targetWindow ) override;

#pragma endregion

};

#endif // !HUD_H
