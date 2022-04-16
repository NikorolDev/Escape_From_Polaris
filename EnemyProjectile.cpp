#include "EnemyProjectile.h"
#include "Settings.h"

EnemyProjectile::EnemyProjectile()
{
	// Set enemy projectile type and its other properites using the Settings.h file
	setProjectileType		( ProjectileTypes::EnemyProjectile );
	setDamage				( Settings::ProjectileProperties::EnemyProjectiles::c_damage );
	setProjectileSpeed		( Settings::ProjectileProperties::EnemyProjectiles::c_speed );
	setProjectileDirection	( 0 , 0.5f );
}

void EnemyProjectile::update(float deltaTime)
{
	// First update a projectile using the base class
	ProjectileBase::update(deltaTime);

	// Check if a projectile are below the screen
	if ( getPosition().y > Settings::Positions::c_lowestPointToDespawn )
	{
		// Destroy the projectile
		setIsProjectileAlive(false);
	}
}
