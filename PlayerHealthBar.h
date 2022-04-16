#ifndef PLAYERHEALTHBAR_H
#define PLAYERHEALTHBAR_H

#include "ProgressionBar.h"

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: PlayerHealthBar
// Classes Inherited	: ProgressionBar
// Purpose				: To handle the the progression value for the health bar fill to be displayed
//-------------------------------------------------------------------------------------------------------------------------
class  PlayerHealthBar : public ProgressionBar
{
public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: PlayerHealthBar()
	// Parameters		: None
	// Notes			: This constructor will set properties of the health bar
	//---------------------------------------------------------------------------------------------------------------------
	PlayerHealthBar();

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: update(float progressionValue)
	// Parameters		: progressionValue - The passed through health points from the player
	// Purpose			: This update function will check if the progression bar can be filled, which will allow the 
	//					,	progression bar to be filled using the base class update
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void update( float progressionValue ) override;

#pragma endregion

};

#endif // !PLAYERHEALTHBAR_H
