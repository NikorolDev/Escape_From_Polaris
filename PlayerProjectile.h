#ifndef PLAYERPROJECTILE_H
#define PLAYERPROJECTILE_H

#include "ProjectileBase.h"

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: PlayerProjectile
// Classes Inherited	: ProjectileBase
// Purpose				: To set unique properties that makes an player projectile and update them
//-------------------------------------------------------------------------------------------------------------------------
class PlayerProjectile : public ProjectileBase
{
public:
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: PlayerProjectile()
	// Parameters		: None
	// Notes			: As this is a default constructor, it will set projectile properties
	//---------------------------------------------------------------------------------------------------------------------
	PlayerProjectile();

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: update(float deltaTime)
	// Parameters		: deltaTime - This won't be used in the child classes as everything is already done in the base 
	//					,	class
	// Purpose			: This update function will update the projectile from base and check if went below the screen
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void update( float deltaTime ) override;
};

#endif // !PLAYERPROJECTILE_H