#include "BiterEnemy.h"
#include "Helpers.h"
#include "Player.h"
#include "Settings.h"

#include <iostream>

BiterEnemy::BiterEnemy()
// Setting these variables before the constructor gets called
	: m_hasMissed				( false )
	, m_deltaTime				( 0.0f )
	, m_lerpFormationPosition	( 0.0f )
	, m_pPlayer					( nullptr )
{
	// Set the enemy type to biter and set properties from the "Settings.h" file and the scale to match other ships
	setEnemyType	( EnemyTypes::Biter );
	setDamageAmount	( Settings::EnemyProperties::BiterProperties::c_damage );
	setHealthPoints	( Settings::EnemyProperties::BiterProperties::c_maxHealthPoints );
	setSpeed		( 0.0f );
	setScale		( 2.0f , 2.0f );
}

void BiterEnemy::initialise( AudioManager* pAudioManager , Player* pPlayer , ProjectileManager* pProjectileManager , TextureManager* pTextureManager )
{
	// Set player pointer
	m_pPlayer = pPlayer;
}

void BiterEnemy::update( float deltaTime )
{
	// Assign delta time
	m_deltaTime = deltaTime;

	// Update the biter first using the base class updater
	EnemyBase::update( m_deltaTime );

	// Animate the biter
	animateSpriteSheet( sf::IntRect( 0 , 0 , Settings::TextureProperties::c_spriteFrameSizeXY , Settings::TextureProperties::c_spriteFrameSizeXY ) ,
						true ,
						m_deltaTime ,
						Settings::TextureProperties::c_maxGeneralAnimationFramesPerSecond ,
						Settings::EnemyProperties::BiterProperties::c_maxAmountOfAnimationFrames );

	// Make the biter enemy attack
	biterAttack();

	// Check if the biter is dead or missed the player
	checkDeathState();
	checkIfMissedThePlayer();
}

void BiterEnemy::reset()
{
	// Reset the health points and reset other values from the enemy base reset function
	setHealthPoints( Settings::EnemyProperties::BiterProperties::c_maxHealthPoints );
	setRotation( 0.0f );
	EnemyBase::reset();
}

void BiterEnemy::biterAttack()
{
	// Check if the biter picked is alive and it can attack
	if ( getIsEnemyAlive() == true && 
		 getCanEnemyAttack() == true )
	{
		// Set the centreline to be player's position
		m_centreline = m_pPlayer->getPosition();

		// Check if the spped of the biter is bigger than 0, so moving right
		if ( getSpeed() >= 0.0f )
		{
			// Then check if the biter's current position is bigger than the max amplitude of the sine wave
			if ( getPosition().x >= ( m_centreline.x + Settings::EnemyProperties::BiterProperties::c_centrelineOffset ) )
			{
				// Start moving left, the opposite direction
				setSpeed(  getSpeed() -  Settings::EnemyProperties::BiterProperties::c_speedIncrementor  * m_deltaTime  );
			}

			// This check will make the sure that the speed is not above 100
			else if ( getSpeed() < Settings::EnemyProperties::BiterProperties::c_maxSpeedX )
			{
				// Move the right, which would be the correct direction as the speed is higher than 0
				setSpeed(  getSpeed() + Settings::EnemyProperties::BiterProperties::c_speedIncrementor  * m_deltaTime );
			}
		}

		// Check if the biter speed is lower than 0, so moving left
		if ( getSpeed() < 0.0f )
		{
			// If the biter's current position is bigger than the minimum amplitude of the sine wave
			if ( getPosition().x <= ( m_centreline.x - Settings::EnemyProperties::BiterProperties::c_centrelineOffset ) )
			{
				// Start moving right, the opposite direction
				setSpeed(  getSpeed() + Settings::EnemyProperties::BiterProperties::c_speedIncrementor  * m_deltaTime );
			}

			// This check will make the sure that the speed is not below negative max speed
			else if ( getSpeed() > -Settings::EnemyProperties::BiterProperties::c_maxSpeedX )
			{
				// Move left, which would be the current direction as the speed is below 0
				setSpeed(  getSpeed() - Settings::EnemyProperties::BiterProperties::c_speedIncrementor  * m_deltaTime );
			}
		}

		// Move the biter in a sine wave, which will have a constant speed on the Y and updated X
		move( getSpeed() , Settings::EnemyProperties::BiterProperties::c_maxSpeedY * m_deltaTime );

		// Set the distance between the enemy and player on the x and y, this will help with getting the rotation that enemy will face the player
		float distanceX = getPosition().x - m_pPlayer->getPosition().x;
		float distanceY = getPosition().y - m_pPlayer->getPosition().y;

		// Set the rotation using tan
		float rotation = ( atan2( distanceY , distanceX ) ) * 180 / Settings::c_pi;

		// Set the calcualted rotation to the biter, so that it will  face the player whilst it is moving down
		setRotation( rotation + 90 );
	}
}

void BiterEnemy::checkDeathState()
{
	// Check if the biter has died
	if ( getIsEnemyAlive() == false )
	{
		// Reset rotation so that when the biter comes back alive in the next wave, they will be facing downwards and not their previosuly known rotation
		setRotation			( 0.0f );

		// Reset these values, so the next biter enemy can be used, if it's alive
		setCanEnemyAttack	( false );
		setSpeed			( 0.0f );
	}
}

void BiterEnemy::checkIfMissedThePlayer()
{
	// Check if the biter has missed the player by checking if its below the screen
	if ( getPosition().y > Settings::Positions::c_lowestPointToDespawn )
	{
		// Set that the biter has missed and reset the values
		m_hasMissed			= true;

		setCanEnemyAttack	( false );
		setSpeed			( 0.0f );
		setRotation			( 0.0f );
	}

	// Check if the biter has missed using the boolean
	if ( m_hasMissed == true )
	{
		// Increment lerp time using deltaTime
		m_lerpFormationPosition += m_deltaTime;

		// Lerp the biter back to its formation position. Using the c_highestPointToDespawn will set the position of the biter above the screen first
		setPosition( vectorLerp( sf::Vector2f( getFormationPosition().x , Settings::Positions::c_highestPointToDespawn ) , getFormationPosition() , m_lerpFormationPosition ) );

		// If the biter enemy is back to its formation position
		if ( m_lerpFormationPosition > 1.0f )
		{
			// Reset the values for the next missed biter enemy
			m_hasMissed				= false;
			m_lerpFormationPosition = 0.0f;
		}
	}
}
