#ifndef POWERUPBAR_H
#define POWERUPBAR_H

#include "ProgressionBar.h"

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: PowerUpBar
// Classes Inherited	: ProgressionBar
// Purpose				: To handle the the progression value for the power up bar fill to be displayed
//-------------------------------------------------------------------------------------------------------------------------
class PowerUpBar : public ProgressionBar
{
public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: PowerUpBar()
	// Parameters		: None
	// Notes			: This constructor will set properties of the power up bar
	//---------------------------------------------------------------------------------------------------------------------
	PowerUpBar();

#pragma endregion
	
#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: update(float progressionValue)
	// Parameters		: progressionValue - The passed through power up points from the player
	// Purpose			: This update function will check if the progression bar can be filled, which will allow the 
	//					,	progression bar to be filled using the base class update
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void update( float progressionValue ) override;

#pragma endregion

};

#endif // !POWERUPBAR_H
