#include "PlayerHealthBar.h"
#include "Settings.h"

PlayerHealthBar::PlayerHealthBar()
{
	// Set the properties needed for the power up bar
	setProgressBar( Settings::ProgressionBarsProperties::PlayerHealthBar::c_playerHealthBarFillPosition , 0.0f , Settings::ProgressionBarsProperties::c_maxProgressionBarHeight, Settings::Colours::c_green );
	setPosition( Settings::ProgressionBarsProperties::PlayerHealthBar::c_playerHealthBarPosition );
}

void PlayerHealthBar::update( float progressionValue )
{
	// If the progression value is less than or equal to maximum value needed, then update the progression bar
	if ( progressionValue >= getMinProgressValue() )
	{
		ProgressionBar::update( progressionValue );
	}
}
