#include "PlayerProjectile.h"
#include "Settings.h"

PlayerProjectile::PlayerProjectile()
{
	// Set player projectile type and its other properites using the Settings.h file
	setProjectileType		( ProjectileTypes::PlayerProjectile );
	setDamage				( Settings::ProjectileProperties::PlayerProjectiles::c_damage );
	setProjectileSpeed		( Settings::ProjectileProperties::PlayerProjectiles::c_speed );
	setProjectileDirection	( 0.0f , -0.5f );
}

void PlayerProjectile::update(float deltaTime)
{
	// First update a projectile using the base class
	ProjectileBase::update( deltaTime );

	// Check if a projectile are above the screen
	if ( getPosition().y < Settings::Positions::c_highestPointToDespawn )
	{
		// Destroy the projectile
		setIsProjectileAlive( false );
	}
}

