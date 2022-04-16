#ifndef PROGRESSIONBAR_H
#define PROGRESSIONBAR_H

#include <SFML/Graphics/RectangleShape.hpp>

#include "SpriteObject.h"

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: ProgressionBar
// Classes Inherited	: SpriteObject
// Purpose				: To handle every single progression bar in this base class
//-------------------------------------------------------------------------------------------------------------------------
class ProgressionBar : public SpriteObject
{
private:
#pragma region private variables
	float m_maxBarHeight; // Max bar height
	float m_maxProgressValue; // Maximum progress value for progression bars that ascend
	float m_minProgressValue; // Minimum progress value for progression bars that descend

	sf::RectangleShape m_progressBar; // The progression fill bar

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: ProgressionBar()
	// Parameters		: None
	// Notes			: As this is a default constructor it will initialise private variables
	//---------------------------------------------------------------------------------------------------------------------
	ProgressionBar();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: EnemyBase()
	// Parameters		: None
	// Notes			: This destructor will delete itself and as it is virtual it will delete the child classes as well
	//---------------------------------------------------------------------------------------------------------------------
	virtual ~ProgressionBar();

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: update(float progressionValue)
	// Parameters		: progressionValue - This will be used to update the progression fill bar
	// Purpose			: This update function will mainly update progression fill bar
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void update( float progressionValue );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: render(sf::RenderTarget* targetWindow)
	// Parameters		: targetWindow - the window to render object to
	// Purpose			: To render the every progression bar onto the screen
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void render( sf::RenderTarget* targetWindow ) override;

#pragma endregion

#pragma region getters and setters
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setProgressBar(sf::Vector2f position , float initialWidth , float maxHeight , sf::Color barFillColour)
	// Parameters		: position - the position of the fill bar
	//					, initialWidth - the initial width of the fill bar
	//					, maxHeight - the maximum height of the bar fill
	//					, barFillColour - the colour of the fill bar
	// Purpose			: This will set the enemy type so it can be recognised and not mistaken by another enemy
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setProgressBar( sf::Vector2f position , float initialWidth , float maxHeight , sf::Color barFillColour );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setMaxProgressValue(float maxProgressValiue)
	// Parameters		: maxProgressValiue - the maximum progress value for progress bar to go up to
	// Purpose			: This will set the maximum progress bar for the fill so it won't go beyond that value
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setMaxProgressValue( float maxProgressValiue );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getMaxProgressValue()
	// Parameters		: None
	// Purpose			: This will get the maximum progression bar value to check if it still can be updated
	// Returns			: Return the maximum progression value
	//---------------------------------------------------------------------------------------------------------------------
	const float getMaxProgressValue() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setMinProgressValue(float minProgressValue)
	// Parameters		: minProgressValue - the minimum progress value for progress bar to go down to
	// Purpose			: This will set the minimum progress bar for the fill so it won't go beyond that value
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setMinProgressValue( float minProgressValue );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getMinProgressValue()
	// Parameters		: None
	// Purpose			: This will get the minimum progression bar value to check if it still can be updated
	// Returns			: Return the minimum progression value
	//---------------------------------------------------------------------------------------------------------------------
	const float getMinProgressValue() const;

#pragma endregion

};

#endif // !PROGRESSIONBAR_H
