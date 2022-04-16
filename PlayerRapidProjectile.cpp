#include "PlayerRapidProjectile.h"
#include "Settings.h"

PlayerRapidProjectile::PlayerRapidProjectile()
{
	// Set rapid projectile type and its other properites using the Settings.h file
	setProjectileType		( ProjectileTypes::PlayerRapidProjectile );
	setDamage				( Settings::ProjectileProperties::RapidFireProjectiles::c_damage );
	setProjectileSpeed		( Settings::ProjectileProperties::RapidFireProjectiles::c_speed );
	setProjectileDirection	( 0.0f , -0.5f );
}

void PlayerRapidProjectile::update( float deltaTime )
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
