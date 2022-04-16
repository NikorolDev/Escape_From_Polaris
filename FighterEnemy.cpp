#include "AudioManager.h"
#include "FighterEnemy.h"
#include "ProjectileManager.h"
#include "Settings.h"

FighterEnemy::FighterEnemy()
// Setting these variables before the constructor gets called
	: m_pAudioManager		( nullptr )
	, m_pProjectileManager ( nullptr )
{
	// Set the enemy type to fighter and set properties from the "Settings.h" file and the scale to match other ships
	setEnemyType(EnemyTypes::Fighter);
	setHealthPoints( Settings::EnemyProperties::FighterProperties::c_maxHealthPoints );
	setScale( 2.0f , 2.0f );
}

void FighterEnemy::initialise( AudioManager* pAudioManager , Player* pPlayer , ProjectileManager* pProjectileManager , TextureManager* pTextureManager )
{
	// Set audio manager and projectile manager
	m_pAudioManager			= pAudioManager;
	m_pProjectileManager	= pProjectileManager;

	// Check if enemy projectiles have already been initialised, by checking if there's already max amount of enemy projectiles set
	if ( m_pProjectileManager->getMaxAmountOfEnemyProjectiles() < Settings::ProjectileProperties::EnemyProjectiles::c_maxAmountOfProjectiles )
	{
		// Initialise 4 enemy projectiles for every fighter and set max amount of enemy projectiles
		m_pProjectileManager->initialiseProjectiles( Settings::ProjectileProperties::EnemyProjectiles::c_maxAmountOfProjectiles , ProjectileTypes::EnemyProjectile , pTextureManager );
		m_pProjectileManager->setMaxAmountOfEnemyProjectiles( Settings::ProjectileProperties::EnemyProjectiles::c_maxAmountOfProjectiles );
	}
}

void FighterEnemy::update( float deltaTime )
{
	// Update the fighter first using the base class updater
	EnemyBase::update( deltaTime );

	// Animate the fighter
	animateSpriteSheet( sf::IntRect( 0 , 0 , Settings::TextureProperties::c_spriteFrameSizeXY , Settings::TextureProperties::c_spriteFrameSizeXY ) ,
						true ,
						deltaTime ,
						Settings::TextureProperties::c_maxGeneralAnimationFramesPerSecond ,
						Settings::EnemyProperties::FighterProperties::c_maxAmountOfAnimationFrames );

	// Shoot projectiles if a fighter can shoot
	shootProjectile();
}

void FighterEnemy::reset()
{
	// Reset the health points and reset other values from the enemy base reset function 
	setHealthPoints( Settings::EnemyProperties::FighterProperties::c_maxHealthPoints );
	EnemyBase::reset();
}

void FighterEnemy::shootProjectile()
{
	// Check if the fighter picked is alive and if it can can attack
	if ( getIsEnemyAlive() == true && 
		 getCanEnemyAttack() == true )
	{
		// The fighter cant attack anymore, so it won't spam projectiles
		setCanEnemyAttack( false );

		// Instantiate an enemy projectile
		ProjectileBase* projectile = m_pProjectileManager->instantiateProjectile( ProjectileTypes::EnemyProjectile );

		// Set the spawning position of the projectile and that it is alive
		projectile->setPosition			( getPosition() );
		projectile->setIsProjectileAlive( true );

		// Play the enemy projectile sound when instantiated
		m_pAudioManager->playAudio( GameSounds::EnemyProjectile );
	}
}