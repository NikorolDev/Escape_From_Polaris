#ifndef ENEMYPROJECTILE_H
#define ENEMYPROJECTILE_H

#include "ProjectileBase.h"

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: EnemyProjectile
// Classes Inherited	: ProjectileBase
// Purpose				: To set unique properties that makes an enemy projectile and update them
//-------------------------------------------------------------------------------------------------------------------------
class EnemyProjectile : public ProjectileBase
{
public:
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: EnemyProjectile()
	// Parameters		: None
	// Notes			: As this is a default constructor, it will set projectile properties
	//---------------------------------------------------------------------------------------------------------------------
	EnemyProjectile();

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: update(float deltaTime)
	// Parameters		: deltaTime - This won't be used in the child classes as everything is already done in the base 
	//					,	class
	// Purpose			: This update function will update the projectile from base and check if went above the screen
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void update( float deltaTime ) override;
};

#endif // !ENEMYPROJECTILE_H
