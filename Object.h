#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics/RenderTarget.hpp>

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: Object
// Classes Inherited	: None
// Purpose				: To handle objects that will have an update and render
//-------------------------------------------------------------------------------------------------------------------------
class Object
{
public:
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: update(float deltaTime)
	// Parameters		: deltaTime - This will be used to make our movements smoother and frame rate independent
	// Purpose			: To update the values of a class
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void update(float deltaTime) {};

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: render(sf::RenderTarget* targetWindow)
	// Parameters		: targetWindow - the window to render object to
	// Purpose			: To render the object on to the screen, so its visible on the screen
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void render(sf::RenderTarget* targetWindow) {};
};

#endif // !OBJECT_H
