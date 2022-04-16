#include "AudioManager.h"
#include "CircleCollider.h"
#include "CollisionManager.h"
#include "EnemyBase.h"
#include "EnemyManager.h"
#include "Player.h"
#include "ProjectileBase.h"
#include "ProjectileManager.h"
#include "Settings.h"

#include <iostream>

CollisionManager::CollisionManager()
{
	//Set these poisnters to nullptr, instead of creating a new one which will be set by the setter function
	m_pAudioManager			= nullptr;
	m_pEnemyManager			= nullptr;
	m_pEnemyProjectile		= nullptr;
	m_pPlayer				= nullptr;
	m_pPlayerProjectile		= nullptr;
	m_pProjectileManager	= nullptr;
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::initialise( AudioManager* pAudioManager , EnemyManager* pEnemyManager,Player* pPlayer, ProjectileManager* pProjectileManager )
{
	// Set the all the pointer and so they won't be nullptrs
	m_pAudioManager			= pAudioManager;
	m_pEnemyManager			= pEnemyManager;
	m_pPlayer				= pPlayer;
	m_pProjectileManager	= pProjectileManager;
}

void CollisionManager::update()
{
	// Loop through all projetiles that are in the vector
	for (auto& projectile : m_pProjectileManager->getProjectiles())
	{
		// Check if each projectile is not a nullptr
		if (projectile != nullptr)
		{
			// Check all collisions relating to projectiles
			checkCollisionBetweenPlayerProjectilesAndEnemies			( projectile );
			checkCollisionBetweenEnemyProjectilesAndPlayer				( projectile );
			checkCollisionBetweenEnemyProjectilesAndPlayerProjectiles	( projectile );
		}
	}
	
	// Check collision between player and enemies
	checkCollisionBetweenPlayerAndEnemy();
}

bool CollisionManager::checkCircleColliderOverlap(const CircleCollider& circleCollider1, const CircleCollider& circleCollider2)
{
	// Create vector 2 to calculate the position difference of 2 circle colliders position difference
	sf::Vector2f positionDifference = circleCollider2.getPosition() - circleCollider1.getPosition();

	// Create a float that will calculate the distance squared itself
	float distanceDelta = calculateDistanceSquared(positionDifference);

	// Get the sum of the both circle collider radiuses
	float radiusValue = circleCollider1.getRadius() + circleCollider2.getRadius();

	// Return a boolean which will check if the distance difference is less than radius of circles squared
	// Which is if the 2 circles overlaped
	return distanceDelta < ( radiusValue * radiusValue );
}

float CollisionManager::calculateDistanceSquared(const sf::Vector2f positionDistanceDifference)
{
	// Square the x and y positions to return the float, which will be the distance difference
	return positionDistanceDifference.x * positionDistanceDifference.x + positionDistanceDifference.y * positionDistanceDifference.y;
}

void CollisionManager::checkCollisionBetweenPlayerProjectilesAndEnemies(ProjectileBase* projectile)
{
	// Check if the projectile is alive and that it is a player projectile type
	if ( projectile->getIsProjectileAlive() == true && projectile->getProjectileType() == ProjectileTypes::PlayerProjectile )
	{
		// Loop through all of the enemies in the vector
		for (auto& enemy : m_pEnemyManager->getEnemies())
		{
			// Check if each enemy is not nullptr and it is alive
			if (enemy != nullptr && 
				enemy->getIsEnemyAlive() == true)
			{
				// Check for cirlce overlap with the enemy and player projectile
				if (checkCircleColliderOverlap(enemy->getCircleCollider(), projectile->getCircleCollider()))
				{
					// Decrease enemy health points by the amount of damage of the player projectile and despawn the projectile
					enemy->setHealthPoints( enemy->getHealthPoints() - projectile->getDamage() );
					projectile->setIsProjectileAlive(false);

					// Check if the enemy is dead and if the player can still get power up points
					if ( enemy->getHealthPoints() <= 0.0f  && 
						 m_pPlayer->getPowerUpPoints() <= Settings::ProgressionBarsProperties::PowerUpBar::c_maxPowerUpPoints )
					{
						// Add power up pointsa and player score 
 						m_pPlayer->setPowerUpPoints( m_pPlayer->getPowerUpPoints() + 10.0f );
					}
					
					// Check if that enemy is dead, by checking their health points and decrement the amount of enemies and updating the player score and play score sound
					if( enemy->getHealthPoints() <= 0.0f )
					{
 						m_pEnemyManager->setEnemiesActive	( m_pEnemyManager->getEnemiesActive() - 1 );
						m_pPlayer->setScore					( m_pPlayer->getScore() + 10 );
						m_pAudioManager->playAudio			( GameSounds::Score );

						//enemy->setIsEnemyAlive( false );
					}
				}
			}
		}
	}

	// Check projectile is alive and if the projectile type is player rapid projectile
	if ( projectile->getIsProjectileAlive() == true && projectile->getProjectileType() == ProjectileTypes::PlayerRapidProjectile )
	{
		// Loop through all of the enemies in the vector
		for ( auto& enemy : m_pEnemyManager->getEnemies() )
		{
			// Check if each enemy is not nullptr and it is alive
			if ( enemy != nullptr &&
				enemy->getIsEnemyAlive() == true )
			{
				// Check for cirlce overlap with the enemy and player projectile
				if ( checkCircleColliderOverlap( enemy->getCircleCollider() , projectile->getCircleCollider() ) )
				{
					// Decrease enemy health points by the amount of damage of the player projectile and despawn the projectile
					enemy->setHealthPoints( enemy->getHealthPoints() - projectile->getDamage() );
					projectile->setIsProjectileAlive( false );

					// Check if the enemy is dead and if the player can still get power up points
					if ( enemy->getHealthPoints() <= 0.0f &&
						m_pPlayer->getPowerUpPoints() <= Settings::ProgressionBarsProperties::PowerUpBar::c_maxPowerUpPoints )
					{
						// Add power up pointsa and player score 
						m_pPlayer->setPowerUpPoints( m_pPlayer->getPowerUpPoints() + 10.0f );
					}

					// Check if that enemy is dead and if their collider is actice, by checking their health points and decrement the amount of enemies and updating the player score and play score sound
					if ( enemy->getHealthPoints() <= 0.0f && enemy->getCircleCollider().getIsActive() == true )
					{
						// Decrement the amount of enemies active upadate score, disable the collider and play score sound
						m_pEnemyManager->setEnemiesActive( m_pEnemyManager->getEnemiesActive() - 1 );
						m_pPlayer->setScore( m_pPlayer->getScore() + 10 );
						enemy->getCircleCollider().setIsActive( false );
						m_pAudioManager->playAudio( GameSounds::Score );
					}
				}
			}
		}
	}
}

void CollisionManager::checkCollisionBetweenEnemyProjectilesAndPlayer(ProjectileBase* projectile)
{
	// Check if the enemy projectile is alive and if it is the enemy projectile type
	if ( projectile->getIsProjectileAlive() == true && 
		 projectile->getProjectileType() == ProjectileTypes::EnemyProjectile )
	{
		// Check collision between player collider and enemy projectile collider
		if ( checkCircleColliderOverlap( m_pPlayer->getCircleCollider() , projectile->getCircleCollider() ) )
		{
			// Destroy the projectile
			projectile->setIsProjectileAlive( false );

			// Check if player's shield is not active
			if ( m_pPlayer->getIsShieldEnabled() == false )
			{
				// Decrease health points by the amount of damage of the enemy projectile
				m_pPlayer->setHealthPoints( m_pPlayer->getHealthPoints() - projectile->getDamage() );
			}
		}
	}
}

void CollisionManager::checkCollisionBetweenEnemyProjectilesAndPlayerProjectiles( ProjectileBase* projectile )
{
	// Check if the projectile is alive
	if ( projectile->getIsProjectileAlive() == true )
	{
		// Check if the projectile that is alive is either an enemy's
		if ( projectile->getProjectileType() == ProjectileTypes::EnemyProjectile )
		{
			// This will set the latest enemy projectile
			m_pEnemyProjectile = projectile;
		}
		// Or if it is player's
		else if ( projectile->getProjectileType() == ProjectileTypes::PlayerProjectile || 
			      projectile->getProjectileType() == ProjectileTypes::PlayerRapidProjectile )
		{
			// Which will will set the latest player projectile
			m_pPlayerProjectile = projectile;
		}

		// Check again if the enemy projectile or player projectile or not null pointers
		if ( m_pEnemyProjectile != nullptr && 
			 m_pPlayerProjectile != nullptr )
		{
			// Check collision with the player's projectile and enemy's projectile
			if ( checkCircleColliderOverlap( m_pPlayerProjectile->getCircleCollider() , m_pEnemyProjectile->getCircleCollider() ) )
			{
				// Despawn both projectiles
				m_pEnemyProjectile->setIsProjectileAlive	( false );
				m_pPlayerProjectile->setIsProjectileAlive	( false );

				// Set them back to null pointers, so that the next projectiles can be used for collision detection
				m_pEnemyProjectile	= nullptr;
				m_pPlayerProjectile = nullptr;
			}
		}
	}
}

void CollisionManager::checkCollisionBetweenPlayerAndEnemy()
{
	// Loop for all enemies
	for ( auto& enemy : m_pEnemyManager->getEnemies() )
	{
		// Check if enemy is not nullptr and if it is alive
		if ( enemy != nullptr &&
			enemy->getIsEnemyAlive() == true )
		{
			// Check if the player is not respawning, which prevents the player taking damage whilst respawning
			if ( m_pPlayer->getIsRespawning() == false )
			{			// Check if the enemy type is a biter enemy
				if ( enemy->getEnemyType() == EnemyTypes::Biter )
				{
					// Check collision between player and a biter
					if ( checkCircleColliderOverlap( m_pPlayer->getCircleCollider() , enemy->getCircleCollider() ) )
					{
						if ( m_pPlayer->getIsShieldEnabled() == false )
						{
							// Decrease health points by damage the biter deals and set the health of the biter to 0, so its dead
							m_pPlayer->setHealthPoints( m_pPlayer->getHealthPoints() - enemy->getDamageAmount() );
							enemy->setHealthPoints( 0.0f );

							// Check if the power up points is less than max power up points
							if ( m_pPlayer->getPowerUpPoints() <= Settings::ProgressionBarsProperties::PowerUpBar::c_maxPowerUpPoints )
							{
								// Add power up points, player score and decrease the amount of enemies active
								m_pPlayer->setPowerUpPoints( m_pPlayer->getPowerUpPoints() + 10.0f );
							}

							if ( enemy->getHealthPoints() <= 0.0f )
							{
								// Add player score and decrease the amount of enemies active and play score sound
								m_pEnemyManager->setEnemiesActive( m_pEnemyManager->getEnemiesActive() - 1 );
								m_pPlayer->setScore( m_pPlayer->getScore() + 5 );
								m_pAudioManager->playAudio( GameSounds::Score );
							}
						}
					}
				}

				// Check if the enemy type is a dasher
				else if ( enemy->getEnemyType() == EnemyTypes::Dasher )
				{
					// Check collision between player and a dasher
					if ( checkCircleColliderOverlap( m_pPlayer->getCircleCollider() , enemy->getCircleCollider() ) )
					{
						// If the circle collider is active
						if ( enemy->getCircleCollider().getIsActive() == true )
						{
							// Check if the player's shield is not active
							if ( m_pPlayer->getIsShieldEnabled() == false )
							{
								// Decrease the players health points
								m_pPlayer->setHealthPoints( m_pPlayer->getHealthPoints() - enemy->getDamageAmount() );
							}
							else // Otherwise, disable shield
							{
								m_pPlayer->setIsShieldEnabled( false );
							}

							// Disable the collider, which will not check overlap that will deal more damage than it needs to
							enemy->getCircleCollider().setIsActive( false );
						}
					}
					else
					{
						// If the dasher is no longer colliding with the player, Check if the collider is disabled
						if ( enemy->getCircleCollider().getIsActive() == false )
						{
							// Renable the collider
							enemy->getCircleCollider().setIsActive( true );
						}
					}
				}
			}
		}
	}
}


