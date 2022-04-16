#include "EnemyBase.h"
#include "Helpers.h"
#include "Settings.h"

EnemyBase::EnemyBase()
// Setting these variables before the constructor gets called
	: m_canAttack				( false )
	, m_canMoveToFormation		( false )
	, m_isInFormation			( false )
	, m_isAlive					( false )
	, m_damage					( 0.0f )
	, m_healthPoints			( 0.0f )
	, m_movementToFormationTime	( 0.0f )
	, m_speed					( 0.0f )
	, m_enemyType				( EnemyTypes::BlankEnemy )
{
	// Set the collider radius for every enemy
	m_circleCollider.setCircleColliderRadius( 20.0f );
}

void EnemyBase::update( float deltaTime )
{
	// Check if the enemy's health is above 0
	if ( m_healthPoints > 0.0f )
	{
		// Check if the enemy can move to formation position
		if ( m_canMoveToFormation == true )
		{
			// Move the enemy to formation
			moveToFormationPosition( deltaTime );
		}
		// Set the circle collider to the enemy's position
		m_circleCollider.setPosition( getPosition() );
	}
	// Otherwise, if enemy's health points are below or equal to 0
	else if ( m_healthPoints <= 0.0f )
	{
		// Disable enemy, so it won;t update and render
		m_isAlive = false;
	}
}

void EnemyBase::render( sf::RenderTarget* targetWindow )
{
	// If in debug mode, render the circle collider
#ifdef _DEBUG
	m_circleCollider.render( targetWindow );
#endif

	// Render the enemy
	targetWindow->draw( *this );
}

void EnemyBase::moveToFormationPosition( float deltaTime )
{
	// Increment the movement formation time, for interpolation
	m_movementToFormationTime += deltaTime;

	// Check if the formation movement time if below 1 and not in formation
	if ( m_movementToFormationTime < 1.0f && m_isInFormation == false )
	{
		// set position of the enemy using the lerp function
		setPosition( vectorLerp( m_spawningPosition , m_formationPosition , m_movementToFormationTime ) );
	}
	else // Otherwise, if movement formation position is above 1
	{
		// Set the enemy is in formation and set movement formation time to 0
		m_isInFormation				= true;
		m_movementToFormationTime	= 0.0f;
	}
}

void EnemyBase::reset()
{
	// Reset these enemy properties
	m_canAttack				= false;
	m_canMoveToFormation	= false;
	m_isInFormation			= false;
	m_spawningPosition		= sf::Vector2f( 0.0f , 0.0f );
	m_formationPosition		= sf::Vector2f( 0.0f , 0.0f );

	// Renable the collider for enemies
	getCircleCollider().setIsActive( true );
}

void EnemyBase::spawnEnemy( const sf::Vector2f& spawnPosition , const sf::Vector2f& formaitonPosition )
{
	// Set spawning position, formaiton position and set enemy is alive to true
	m_spawningPosition	= spawnPosition;
	m_formationPosition = formaitonPosition;
	m_isAlive			= true;
}

void EnemyBase::setEnemyType( const EnemyTypes enemyType )				{ m_enemyType = enemyType; }

const EnemyTypes& EnemyBase::getEnemyType() const						{ return m_enemyType; }

void EnemyBase::setCanEnemyAttack( bool canAttack )						{ m_canAttack = canAttack; }

const bool EnemyBase::getCanEnemyAttack() const							{ return m_canAttack; }

void EnemyBase::setCanEnemyMoveToFormation( bool canMoveToFormation )	{ m_canMoveToFormation = canMoveToFormation; }

void EnemyBase::setIsEnemyAlive( bool isEnemyAlive )					{ m_isAlive = isEnemyAlive; }

const bool EnemyBase::getIsEnemyAlive() const							{ return m_isAlive; }

const bool EnemyBase::getIsInFomation() const							{ return m_isInFormation; }

void EnemyBase::setDamageAmount( float damageAmount )					{ m_damage = damageAmount; }

const float EnemyBase::getDamageAmount() const							{ return m_damage; }

void EnemyBase::setHealthPoints( float healthPoints )					{ m_healthPoints = healthPoints; }

const float EnemyBase::getHealthPoints() const							{ return m_healthPoints; }

void EnemyBase::setSpeed( float speed )									{ m_speed = speed; }

const float EnemyBase::getSpeed() const									{ return m_speed; }

const sf::Vector2f& EnemyBase::getFormationPosition() const				{ return m_formationPosition; }

CircleCollider& EnemyBase::getCircleCollider()							{ return m_circleCollider; }
