#include "PowerUpBar.h"
#include "Settings.h"

PowerUpBar::PowerUpBar()
{
	// Set the properties needed for the power up bar
	setMaxProgressValue	( Settings::ProgressionBarsProperties::PowerUpBar::c_maxPowerUpPoints );
	setProgressBar		( Settings::ProgressionBarsProperties::PowerUpBar::c_powerUpBarFillPosition , 0.0f , Settings::ProgressionBarsProperties::c_maxProgressionBarHeight , Settings::Colours::c_green );
	setPosition			( Settings::ProgressionBarsProperties::PowerUpBar::c_powerUpBarPosition );
}

void PowerUpBar::update( float progressionValue )
{
	// If the progression value is less than or equal to maximum value needed, then update the progression bar
	if ( progressionValue <= getMaxProgressValue() )
	{
		ProgressionBar::update( progressionValue );
	}
}
