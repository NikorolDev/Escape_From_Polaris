#include <SFML/Window/Keyboard.hpp>

#include "AudioManager.h"
#include "Helpers.h"
#include "Player.h"
#include "PlayerHealthBar.h"
#include "PowerUpBar.h"
#include "ProjectileManager.h"
#include "Settings.h"
#include "TextureManager.h"

Player::Player()
// Setting these variables before the constructor gets called
	: m_canShoot					( true )
	, m_isAnimationLooping			( false )
	, m_deltaTime					( 0.0f )
	, m_maxAnimationFramesPerSecond	( 0.0f )
	, m_maxFramesInAnimation		( 0 )
	, m_pProjectileManager			( nullptr )
{
	// Set the player, to set its position and initialising other variables that would be reset when exiting to main menu
	setPlayer();

	// Set the collision radius for the player and scale
	m_circleCollider.setCircleColliderRadius(20.0f);
	setScale( 2.0f , 2.0f );
}

Player::~Player()
{
}

void Player::initialise( AudioManager* pAudioManager , ProjectileManager* projectileManager , TextureManager* pTextureManager )
{
	// Set audio manager, projectile manager and texture manager
	m_pAudioManager			= pAudioManager;
	m_pProjectileManager	= projectileManager;

	// Initialise player projectiles by setting the max amount needed and the type
	m_pProjectileManager->initialiseProjectiles( 15 , ProjectileTypes::PlayerProjectile , pTextureManager );
	m_pProjectileManager->initialiseProjectiles( 20 , ProjectileTypes::PlayerRapidProjectile , pTextureManager );

	// Load the player's texture to be rended
	loadSpriteTexture( pTextureManager->getTexture( GameTextures::PlayerTexture ) , true );
}

void Player::update(float deltaTime)
{
	// Set the delta time with the one that is passed through
	m_deltaTime = deltaTime;
	
	if ( m_isAlive == true )
	{
		// Animate the player sprite current state
		animateState();

		// Update the movement and the firing of projectiles and initiation of powerUps
		checkDeathState();

		// Check if the player is not respawning
		if ( m_isRespawning == false )
		{
			// Allow the player fire projectiles, initiate power ups and move
			firingProjectiles();
			initiatePowerUp();
			movement();
		}
	}
}

void Player::render( sf::RenderTarget* targetWindow )
{
	// Check if player is alive
	if ( m_isAlive == true )
	{
		// Render the player
		targetWindow->draw( *this );
	}
}

void Player::setPlayer()
{
	// Set all these values that will be reset when restarting the game from the main menu
	m_isAlive				= true;
	m_hasAnimationPicked	= false;
	m_isHealing				= false;
	m_isPowerUpInUse		= false;
	m_isRapidFireEnabled	= false;
	m_isRespawning			= true;
	m_isShieldEnabled		= false;
	m_movementLerpPosition	= 0.5f;
	m_powerUpPoints			= 0.0f;
	m_rapidFireDelayTime	= 1.0f;
	m_healthPoints			= Settings::PlayerProperties::c_maxHealth;
	m_lives					= Settings::PlayerProperties::c_maxLives;
	m_score					= 0;
	m_animationState		= PlayerAnimationState::Respawning;

	// Set the position of the player, which will be at the middle of the screen
	setPosition( 400.0f , Settings::PlayerProperties::c_positionY );
}

void Player::animateState()
{
	// Check if an animation has been picked
	if ( m_hasAnimationPicked == false )
	{
		// If not reinitialise animation
		setHasSpriteAnimationInitialised( false );

		// Based on the animation state
		switch ( m_animationState )
		{
			// For every animation has their texture coordinates,
			// If its a looping animation,
			// Max frames per second, so how quick the animation it is
			// Max amount of frames in the animation
			case PlayerAnimationState::Healing:
			{
				// Healing is not looping and twice as fast as other the moving animation
				// Once the animation ends it will disable the power up usage
				m_animationStateSheet			= sf::IntRect( 0 , Settings::PlayerProperties::Animations::c_textureHealingCoordinateY , Settings::TextureProperties::c_spriteFrameSizeXY , Settings::TextureProperties::c_spriteFrameSizeXY );
				m_isAnimationLooping			= false;
				m_maxAnimationFramesPerSecond	= 0.05f;
				m_maxFramesInAnimation			= 20;
				break;
			}

			case PlayerAnimationState::Moving:
			{
				// The default animation
				m_animationStateSheet			= sf::IntRect( 0 , Settings::PlayerProperties::Animations::c_textureMovingCoordinateY , Settings::TextureProperties::c_spriteFrameSizeXY , Settings::TextureProperties::c_spriteFrameSizeXY );
				m_isAnimationLooping			= true;
				m_maxAnimationFramesPerSecond	= Settings::TextureProperties::c_maxGeneralAnimationFramesPerSecond;
				m_maxFramesInAnimation			= Settings::PlayerProperties::Animations::c_maxFramesForMovingAnimation;
				break;
			}

			case PlayerAnimationState::Respawning:
			{
				// Respawning animation is much slower so that there's a flicker of the player respawning, just like in the old classic arcade games
				m_animationStateSheet			= sf::IntRect( 0 , Settings::PlayerProperties::Animations::c_textureRespawningCoordinateY , Settings::TextureProperties::c_spriteFrameSizeXY , Settings::TextureProperties::c_spriteFrameSizeXY );
				m_isAnimationLooping			= false;
				m_maxAnimationFramesPerSecond	= 0.5f;
				m_maxFramesInAnimation			= 10;
				break;
			}

			case PlayerAnimationState::Shielding:
			{
				// Sheilding animation has a time limit on it, but it is a looping animation as it has the same frame rate and amount of frames as the moving animation
				m_animationStateSheet			= sf::IntRect( 0 , Settings::PlayerProperties::Animations::c_textureShieildingCoordinateY , Settings::TextureProperties::c_spriteFrameSizeXY , Settings::TextureProperties::c_spriteFrameSizeXY );
				m_isAnimationLooping			= true;
				m_maxAnimationFramesPerSecond	= Settings::TextureProperties::c_maxGeneralAnimationFramesPerSecond;
				m_maxFramesInAnimation			= Settings::PlayerProperties::Animations::c_maxFramesForMovingAnimation;
				break;
			}
		}

		// Once animation has been picked, set that animation has been picked to true
		m_hasAnimationPicked = true;
	}

	// Animate the sprite the sheet, based on the aniamtion state that was picked
	animateSpriteSheet(m_animationStateSheet, m_isAnimationLooping , m_deltaTime, m_maxAnimationFramesPerSecond , m_maxFramesInAnimation );

	// Check if aniamtion has finished and the animation not a looping animation
	if ( getHasAnimationFinished() == true && m_isAnimationLooping == false )
	{
		// Check if the current animation state is a healing
		if ( m_animationState == PlayerAnimationState::Healing )
		{
			// Disable power up is use, so the next power up can be used
			m_isPowerUpInUse = false;
		}

		// Set the animation state back to moving (default)
		setAnimationToMoving();
	}
}

void Player::checkDeathState()
{
	// Check if the player is not respawning
	if ( m_isRespawning == false )
	{
		// If player's health is below 0, but has more lives
		if ( m_healthPoints <= 0.0f &&
			 m_lives > 0 )
		{
			// Decrement the amount of lives
			m_lives--;

			// Set respawning to true, set animation state to respawning and allow this animation to be picked
			m_isRespawning			= true;
			m_animationState		= PlayerAnimationState::Respawning;
			m_hasAnimationPicked	= false;
		}

		// Check if the player has no more lives left
		if ( m_lives == 0 )
		{
			// The enemy is dead, which will take the user to the high score screen
			m_isAlive = false;
		}
	}
	// If respawning is true
	else
	{
		// Check if the animation has been finished
		if ( getHasAnimationFinished() == true )
		{
			// Set the respawning to be false and set health points back to full
			m_isRespawning = false;
			m_healthPoints = Settings::PlayerProperties::c_maxHealth;

			// Set animation back to moving
			setAnimationToMoving();
		}
	}
}

void Player::firingProjectiles()
{
	// Check if the player has pressed space
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		// Check if the player can shoo yet. This will stop multiple bullets being spawned at once
		if (m_canShoot == true)
		{
			// The player cant shoot and add a projectile into the game
			m_canShoot = false;

			// Setting up a local variable to a projectile base will instantiate the projectile once and set it to the player projectile using the enum
			ProjectileBase* projectile = m_pProjectileManager->instantiateProjectile(ProjectileTypes::PlayerProjectile);

			// Then set the position and is alive so this projectile can update itself
			projectile->setPosition( getPosition() );
			projectile->setIsProjectileAlive( true );

			// Play player projectile sound
			m_pAudioManager->playAudio( GameSounds::PlayerProjectile );
		}
	}
	else // When the player let's go of the space key the player can shoot again
	{
		m_canShoot = true;
	}
}

void Player::initiatePowerUp()
{
	// Check if a power up is already in use
	if ( m_isPowerUpInUse == false )
	{
		// Check if the player has right amount of points to activate the shield
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Num1 ) &&
			m_powerUpPoints >= Settings::ProgressionBarsProperties::PowerUpBar::c_shieldPointsRequired )
		{
			// Shiled is active so power up is in use
			m_isPowerUpInUse = true;

			// Set the animation to shielding
			m_animationState = PlayerAnimationState::Shielding;
			m_hasAnimationPicked = false;

			// Take away the power up points and enable shield
			m_powerUpPoints -= Settings::ProgressionBarsProperties::PowerUpBar::c_shieldPointsRequired;
			m_isShieldEnabled = true;
		}

		// Check if the player has right amount of points to activate healing
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Num2 ) &&
			m_powerUpPoints >= Settings::ProgressionBarsProperties::PowerUpBar::c_healingPointsRequired )
		{
			// Healing is active so power up is in use
			m_isPowerUpInUse = true;

			// Set the animation to healing
			m_animationState = PlayerAnimationState::Healing;
			m_hasAnimationPicked = false;

			// Take away the power up points
			m_powerUpPoints -= Settings::ProgressionBarsProperties::PowerUpBar::c_healingPointsRequired;

			// Set healing points by, checking if health points is more than what healing gives
			if ( m_healthPoints > Settings::PlayerProperties::c_healingPoints )
			{
				// Set the healthpoints to max, so that it doesn't go beyond the bar
				m_healthPoints = Settings::PlayerProperties::c_maxHealth;
			}
			// Check if health points less than healing amount
			else if ( m_healthPoints <= Settings::PlayerProperties::c_healingPoints )
			{
				// Add healing amount to health points
				m_healthPoints += Settings::PlayerProperties::c_healingPoints;
			}
		}

		// Check if the player has right amount of points to activate rapid fire
		if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Num3 ) && m_powerUpPoints >= Settings::ProgressionBarsProperties::PowerUpBar::c_maxPowerUpPoints )
		{
			// Rapid fire is active so power up is in use 
			m_isPowerUpInUse = true;

			// Take away the power up points and enable rapid fire
			m_powerUpPoints -= Settings::ProgressionBarsProperties::PowerUpBar::c_maxPowerUpPoints;
			m_isRapidFireEnabled = true;

		}
	}

	// Check if any of these power ups are enabled and function them
	shieldActiveChecker();
	rapidFireAcitveChecker();
}

void Player::shieldActiveChecker()
{
	// Check if shield is enabled
	if ( m_isShieldEnabled == true )
	{
		// Increment the time of shield being active
		m_shieldActivationTime += m_deltaTime;

		// Check if shield's time has run out
		if ( m_shieldActivationTime > Settings::PlayerProperties::c_maxTimeForShieldActivation )
		{
			// Disable shielding,  disable power up, reset activation time and set the animation back to moving( default )
			m_isShieldEnabled		= false;
			m_isPowerUpInUse		= false;
			m_shieldActivationTime	= 0.0f;
			setAnimationToMoving();
		}
	}

	// Check if the sheild has been deactivated whilst being active
	if ( m_isShieldEnabled == false && m_shieldActivationTime > 0.0f )
	{
		// Disable power up, reset activation time and set the animation back to moving( default )
		m_isPowerUpInUse		= false;
		m_shieldActivationTime	= 0.0f;
		setAnimationToMoving();
	}
}

void Player::rapidFireAcitveChecker()
{
	// Check if rapid fire is enabled
	if ( m_isRapidFireEnabled == true )
	{
		// Increment both activation time and delay time by delta time
		m_rapidFireActivationTime += m_deltaTime;
		m_rapidFireDelayTime += m_deltaTime;

		// Check if projectiles can be shot
		if ( m_rapidFireDelayTime > 0.1f )
		{
			// Reset the delay time
			m_rapidFireDelayTime = 0.0f;

			// Instantiate first projectile on the left side of the player, which in the texture it's the gun
			ProjectileBase* projectile1 = m_pProjectileManager->instantiateProjectile( ProjectileTypes::PlayerRapidProjectile );
			projectile1->setPosition( sf::Vector2f( getPosition().x - Settings::PlayerProperties::c_rapidFireProjectileOffsetPosition , getPosition().y ) );
			projectile1->setIsProjectileAlive( true );

			// Instantiate second projectile on the right side of the player
			ProjectileBase* projectile2 = m_pProjectileManager->instantiateProjectile( ProjectileTypes::PlayerRapidProjectile );
			projectile2->setPosition( sf::Vector2f( getPosition().x + Settings::PlayerProperties::c_rapidFireProjectileOffsetPosition , getPosition().y ) );
			projectile2->setIsProjectileAlive( true );

			// Play player projectile sound
			m_pAudioManager->playAudio( GameSounds::PlayerProjectile );
		}

		// Check if rapid fire's time has ran out
		if ( m_rapidFireActivationTime > Settings::PlayerProperties::c_maxTimeForRapidFireActivation )
		{
			// Disable rapid fire and reset values
			m_isRapidFireEnabled		= false;
			m_isPowerUpInUse			= false;
			m_rapidFireDelayTime		= 1.0f;
			m_rapidFireActivationTime	= 0.0f;
		}
	}
}

void Player::movement()
{
	// Set the positions of the left and right boundary
	sf::Vector2f leftBoundary = sf::Vector2f( Settings::Positions::c_leftBoundaryPositionX, getPosition().y);
	sf::Vector2f rightBoundary = sf::Vector2f( Settings::Positions::c_rightBoundaryPositionX, getPosition().y);

	// Check if the player presses A and if the lerp position is bigger than 0, which is at the left boundary
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) && m_movementLerpPosition >= 0 )
	{
		// Move the player to the left, by lerping position using speed and deltaTime
		m_movementLerpPosition -= Settings::PlayerProperties::c_speed * m_deltaTime;
	}

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) && m_movementLerpPosition <= 1 )
	{
		// Move the player to the right, by lerping position using speed and deltaTime
		m_movementLerpPosition += Settings::PlayerProperties::c_speed * m_deltaTime;
	}

	// Set the position using lerp which will return a vector2
	setPosition( vectorLerp( leftBoundary , rightBoundary , m_movementLerpPosition ) );

	// Set the position of the collider that is corresponding to the player's position
	m_circleCollider.setPosition( getPosition() );
}

void Player::setAnimationToMoving()
{
	// set animation state to moving (default)
	m_animationState		= PlayerAnimationState::Moving;
	m_hasAnimationPicked	= false;
}

void Player::setIsPlayerAlive( bool isPlayerAlive )				{ m_isAlive = isPlayerAlive; }

const bool Player::getIsPlayerAlive() const						{ return m_isAlive; }

const bool Player::getIsRespawning() const						{ return m_isRespawning; }

void Player::setIsShieldEnabled( bool isShieldEnabled )			{ m_isShieldEnabled = isShieldEnabled; }

const bool Player::getIsShieldEnabled() const					{ return m_isShieldEnabled; }

void Player::setHealthPoints( float healthPoints )				{ m_healthPoints = healthPoints; }

const float Player::getHealthPoints() const						{ return m_healthPoints; }

void Player::setPowerUpPoints( float powerUpPoints )			{ m_powerUpPoints = powerUpPoints; }

const float Player::getPowerUpPoints() const					{ return m_powerUpPoints; }

const int Player::getLives() const								{ return m_lives; }

void Player::setScore( int score )								{ m_score = score; }

const int Player::getScore() const								{ return m_score; }

const CircleCollider& Player::getCircleCollider() const			{ return m_circleCollider; }
