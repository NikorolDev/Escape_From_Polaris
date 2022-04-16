#include "DasherEnemy.h"
#include "Helpers.h"
#include "Player.h"
#include "Settings.h"

DasherEnemy::DasherEnemy()
// Setting these variable before the constructor gets called
	: m_hasMissed						( false )
	, m_isAttacking						( false )
	, m_isCharging						( false )
	, m_attackDelayTime					( 0.0f )
	, m_deltaTime						( 0.0f )
	, m_lerpToFormationPositionValue	( 0.0f )
	, m_lerpToPlayerValue				( 0.0f )
	, m_pPlayer							( nullptr )
{
	// Set the enemy type and set properties from the "Settings.h" file and the scale to match other ships
	setEnemyType	( EnemyTypes::Dasher );
	setDamageAmount	( Settings::EnemyProperties::DasherProperties::c_damage );
	setHealthPoints	( Settings::EnemyProperties::DasherProperties::c_maxHealthPoints );
	setSpeed		( Settings::EnemyProperties::DasherProperties::c_speed );
	setScale( 2.0f , 2.0f );
}

void DasherEnemy::initialise( AudioManager* pAudioManager , Player* pPlayer , ProjectileManager* pProjectileManager , TextureManager* pTextureManager )
{
	// Set player pointer
	m_pPlayer = pPlayer;
}

void DasherEnemy::update( float deltaTime )
{
	// Assign delta time
	m_deltaTime = deltaTime;

	// Update the dasher first using the base class updater
	EnemyBase::update( deltaTime );

	// Animate the dasher
	animateSpriteSheet( sf::IntRect( 0 , 0 , Settings::TextureProperties::c_spriteFrameSizeXY , Settings::TextureProperties::c_spriteFrameSizeXY ) ,
						true ,
						m_deltaTime ,
						Settings::TextureProperties::c_maxGeneralAnimationFramesPerSecond ,
						Settings::EnemyProperties::DasherProperties::c_maxAmountOfAnimationFrames );

	// Make the dasher attack
	dasherAttack();

	// Check if the biter is dead or missed the player
	checkDeathState();
	checkIfMissedPlayer();
}

void DasherEnemy::reset()
{
	// Reset the health points and reset other values from the enemy base reset function
	setHealthPoints( Settings::EnemyProperties::DasherProperties::c_maxHealthPoints );
	EnemyBase::reset();
}

void DasherEnemy::dasherAttack()
{
	// Check if the dasher is alive and it can attack
	if ( getIsEnemyAlive() == true && 
		 getCanEnemyAttack() == true )
	{
		// To start the attack, the dasher should lerp to where the player is, before they start cahrging their attack
		// Check if the enemy is not at player's position. So the lerp is less than 1

		if ( m_isCharging == false )
		{
			if ( m_lerpToPlayerValue < 1.0f )
			{
				// Increment the lerp value
				m_lerpToPlayerValue += m_deltaTime;

				// Lerp the dasher from its formation position to the player's position
				setPosition( vectorLerp( getFormationPosition() , sf::Vector2f( m_pPlayer->getPosition().x , 400.0f ) , m_lerpToPlayerValue ) );
			}
			else
			{
				m_isCharging = true;
			}
		}
		else // If it's already on player's position
		{
			// Start charging the attack
			m_attackDelayTime += m_deltaTime;

			// If the dasher is not charged for attack
			if ( m_attackDelayTime < Settings::EnemyProperties::DasherProperties::c_maxTimeToCharge )
			{
				// Keep following the player
				setPosition( m_pPlayer->getPosition().x , getPosition().y );
			}
			else // If the dasher is charged, attack 
			{
				m_isAttacking = true;
			}
		}

		// If the dasher is attacking
		if ( m_isAttacking == true )
		{
			// Move the dasher downwards towards the player
			move( sf::Vector2f( 0.0f , Settings::EnemyProperties::DasherProperties::c_directionY ) * getSpeed() * m_deltaTime );
		}
	}
}

void DasherEnemy::checkDeathState()
{
	// If the enemy died
	if ( getIsEnemyAlive() == false )
	{
		// Reset the values and that it is not attacking so the next dasher can be used for attacking
		setCanEnemyAttack	( false );
		m_isAttacking		= false;
		m_isCharging		= false;
		m_attackDelayTime	= 0.0f;
		m_lerpToPlayerValue = 0.0f;
	}
}

void DasherEnemy::checkIfMissedPlayer()
{
	// Check if the dasher missed the player and is below the screen
	if ( getPosition().y > Settings::Positions::c_lowestPointToDespawn )
	{
		// Set the boolean that the dasher has missed, which will be used to get it back to its position
		m_hasMissed			= true;

		// Disable the enemy attack
		setCanEnemyAttack	( false );
	}

	// Check if the dasher has missed using the boolean
	if ( m_hasMissed == true )
	{
		// Increment lerp time using deltaTime
		m_lerpToFormationPositionValue += m_deltaTime;

		// Lerp the dasher back to its formation position. Using the c_highestPointToDespawn will set the position of the biter above the screen first
		setPosition( vectorLerp( sf::Vector2f( getFormationPosition().x , Settings::Positions::c_highestPointToDespawn ) , getFormationPosition() , m_lerpToFormationPositionValue ) );

		// If the dasher enemy is back to its formation position
		if ( m_lerpToFormationPositionValue > 1.0f )
		{
			// Reset the values for the next missed dasher enemy
			m_hasMissed						= false;
			m_lerpToFormationPositionValue	= 0.0f;

			// Reset this as well, just in case the same enemy is picked
			m_isAttacking					= false;
			m_isCharging					= false;
			m_attackDelayTime				= 0.0f;
			m_lerpToPlayerValue				= 0.0f;
		}
	}
}