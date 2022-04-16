#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include <SFML/Graphics/CircleShape.hpp>

#include "Object.h"

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: CircleCollider
// Classes Inherited	: Object and sf::CircleShape
// Purpose				: To set each necessary object with a circle collider for collision detection
//-------------------------------------------------------------------------------------------------------------------------
class CircleCollider : public Object , public sf::CircleShape
{
private:
#pragma region private variables
	bool	m_isActive; // If the collider will be on or not

	float	m_radius; // The radius of circle collider

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CircleCollider()
	// Parameters		: None
	// Notes			: This constructor will the radius to 0 as the whole collider will be set when 
	//---------------------------------------------------------------------------------------------------------------------
	CircleCollider();

	//---------------------------------------------------------------------------------------------------------------------
	// Desstructor name	: CircleCollider()
	// Parameters		: None
	// Notes			: This destructor will delete nothing
	//---------------------------------------------------------------------------------------------------------------------
	~CircleCollider();

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: render(sf::RenderTarget* targetWindow)
	// Parameters		: targetWindow - the window to render object to
	// Purpose			: To render the circle collider on to the screen. This will only be rendered in debugger mode
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void render( sf::RenderTarget* targetWindow ) override;

#pragma endregion

#pragma region getters and setters

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setIsActive( bool isActive )
	// Parameters		: isActive - Allowing the collider to collide with other colliders
	// Purpose			: To set if the collider will be active or not
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setIsActive( bool isActive );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getIsActive()
	// Parameters		: None
	// Purpose			: To get the boolean of the collider being active
	// Returns			: Return the boolean of the collider being active
	//---------------------------------------------------------------------------------------------------------------------
	const bool getIsActive() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: setCircleColliderRadius(float radius)
	// Parameters		: radius - The desired radius of the collider
	// Purpose			: To set the radius of the collider and set the origin of the collider
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setCircleColliderRadius( float radius );


#pragma endregion

};

#endif // !CIRCLECOLLIDER_H
