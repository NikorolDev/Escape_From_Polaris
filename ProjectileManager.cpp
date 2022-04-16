#include "EnemyManager.h"
#include "EnemyProjectile.h"
#include "Helpers.h"
#include "PlayerProjectile.h"
#include "PlayerRapidProjectile.h"
#include "ProjectileBase.h"
#include "ProjectileManager.h"
#include "TextureManager.h"
#include "Settings.h"

ProjectileManager::ProjectileManager()
// Setting this variable before the constructor gets called
	: m_maxAmountOfEnemyProjectiles		( 0 )
{
	// Set the max size of the projectiles
	m_projectiles.resize( Settings::ProjectileProperties::c_maxAmountOfProjectiles );
}

ProjectileManager::~ProjectileManager()
{
	// Go through all projectiles
	for ( auto& projectile : m_projectiles )
	{
		// Check if the projectile has been created
		if ( projectile != nullptr )
		{
			// Delete them
			delete projectile;
			projectile = nullptr;
		}
	}
}

void ProjectileManager::update( float deltaTime )
{
	// Go through all projectiles
	for ( auto& projectile : m_projectiles )
	{
		// Check if its created
		if ( projectile != nullptr )
		{
			// Check if the projectile is alive
			if ( projectile->getIsProjectileAlive() == true )
			{
				// Update the projectile
				projectile->update( deltaTime );
			}
		}
	}
}

void ProjectileManager::render( sf::RenderTarget* targetWindow )
{
	// Go through all projectiles
	for ( auto& projectile : m_projectiles )
	{
		// Check if the projectile has been created already
		if ( projectile != nullptr )
		{
			// Check if the projectile is alive
			if ( projectile->getIsProjectileAlive() == true )
			{
				// Render the projectile
				projectile->render( targetWindow );
			}
		}
	}
}

void ProjectileManager::initialiseProjectiles( int maxAmountOfProjectiles, const ProjectileTypes& projectileType , TextureManager* pTextureManager )
{
	// Create an int for projectile counting
	int projectileCounter = 0;

	// Go through all projectiles
	for ( auto& projectile : m_projectiles )
	{
		// If that projectile has not been created and check if the counter is less than the max amount of projectiles needed for that type
		if ( projectile == nullptr && 
			 projectileCounter < maxAmountOfProjectiles )
		{
			// Switch to create a new projectile based on what type is needed 
			switch ( projectileType )
			{
				// Each projectile will create a new one, which will call their contructors
				// Then set the correct texture of that projectile
				case ProjectileTypes::PlayerProjectile: // Create new Player projectile
				{
					projectile = new PlayerProjectile();
					projectile->loadSpriteTexture( pTextureManager->getTexture( GameTextures::ProjectilePlayerTexture ) , false );
					break;
				}

				case ProjectileTypes::EnemyProjectile: // Create new Enemy projectile
				{
					projectile = new EnemyProjectile();
					projectile->loadSpriteTexture( pTextureManager->getTexture( GameTextures::ProjectileEnemyTexture ) , false );
					break;
				}

				case ProjectileTypes::PlayerRapidProjectile: // Create new rapid fire projectile
				{
					projectile = new PlayerRapidProjectile();
					projectile->loadSpriteTexture( pTextureManager->getTexture( GameTextures::ProjectileRapidPlayerTexture ) , false );
				}
			}

			// Increment the count of projectiles
			projectileCounter++;
		}
	}
}

ProjectileBase* ProjectileManager::instantiateProjectile( const ProjectileTypes& projectileType )
{
	// Go through all projectiles
	for ( auto& projectile : m_projectiles )
	{
		// Check if the projectile have been created
		if ( projectile != nullptr )
		{
			// Check if it is alive and the current projectile in the loop mathces the type that needs to be instantiated
			if ( projectile->getIsProjectileAlive() == false && projectile->getProjectileType() == projectileType )
			{
				// Return the projectile
				return projectile;
				break;
			}
		}
	}

	// If no criteria has matched, then return a nullptr
	return nullptr;
}

void ProjectileManager::clearProjectiles()
{
	// Go through all projectiles
	for ( auto& projectile : m_projectiles )
	{
		// Check if the projectile has been created
		if ( projectile != nullptr )
		{
			// Deactivate the projectile, which clear it off the screen
			projectile->setIsProjectileAlive( false );
		}
	}
}

void ProjectileManager::setMaxAmountOfEnemyProjectiles( int maxAmountOfEnemyProjectiles )	{ m_maxAmountOfEnemyProjectiles = maxAmountOfEnemyProjectiles; }

const int ProjectileManager::getMaxAmountOfEnemyProjectiles() const							{ return m_maxAmountOfEnemyProjectiles; }

std::vector<ProjectileBase*>& ProjectileManager::getProjectiles()							{ return m_projectiles; }
