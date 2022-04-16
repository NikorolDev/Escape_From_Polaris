#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System/Clock.hpp>

#include "CircleCollider.h"
#include "SpriteObject.h"

//Forward class declaration of ProjectileManager to resolve circular includes and to set a pointer of that class
class AudioManager;
class ProjectileManager;
class TextureManager;

enum class PlayerAnimationState
{
	Healing, Moving , Respawning, Shielding
};

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: Player
// Classes Inherited	: SpriteObject
// Purpose				: To handle how the player will move and how it will fire projectiles
//-------------------------------------------------------------------------------------------------------------------------
class Player : public SpriteObject
{
private:
#pragma region private variables
	bool m_canShoot; //This will check if the player can shoot
	bool m_isAlive; // This will check if the player is alive
	bool m_isAnimationLooping; // To set the animation to be looping
	bool m_isHealing; // This is to check if the player is healing
	bool m_isPowerUpInUse; // This will check if a power up is in use
	bool m_isRapidFireEnabled; // This will check if rapid fire is enabled
	bool m_isRespawning; // This will check if the player is respawning
	bool m_isShieldEnabled; // This will check if the sheild is enabled
	bool m_hasAnimationPicked; // This will check if an animation has been picked

	float m_deltaTime; //The deltaTime that will be used to update the player's movement frame rate independently
	float m_healthPoints; // The current amount of health points
	float m_maxAnimationFramesPerSecond; //The amount of frames per second in an animation
	float m_movementLerpPosition; //The lerp position of the player between the left and right boundary
	float m_powerUpPoints; // Points value for power ups to be used
	float m_rapidFireActivationTime; // The rapid fire activation time
	float m_rapidFireDelayTime; // The delay time of the next rapid fire projectiles to spawn
	float m_shieldActivationTime; // The time that the shield has been active

	int m_lives; // The current amount of lives
	int m_maxFramesInAnimation; // Max amount of frames in an animation
	int m_score; // The current amount of score

	AudioManager* m_pAudioManager; // This will play player projectile sound
	CircleCollider m_circleCollider; // The circle collider that is attached to the player
	PlayerAnimationState m_animationState; // The animation state the player is in
	ProjectileManager* m_pProjectileManager; //The projectile manager to add projectiles whenever the player presses the firing key

	sf::IntRect m_animationStateSheet; // The beginning texture rectangle of an animation

#pragma endregion

#pragma region private functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: animateState()
	// Parameters		: None
	// Purpose			: This will animate the state that was given and change states
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void animateState();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: checkDeathState()
	// Parameters		: None
	// Purpose			: This will check if the player is dead, checking if the player has enough lives to respawn, or 
	//					,	not to end the game
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void checkDeathState();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: firingProjectiles()
	// Parameters		: None
	// Purpose			: To add a single projectile on to the screen when the player hits the firing key
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void firingProjectiles();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: initiatePowerUp()
	// Parameters		: None
	// Purpose			: To initiate the power up only if the plauer has enough points to activate any of them
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void initiatePowerUp();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: shieldActiveChecker()
	// Parameters		: None
	// Purpose			: This will check if the shiled is active, which will change animation state and enable the timer 
	//					,	of activation
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void shieldActiveChecker();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: rapidFireAcitveChecker()
	// Parameters		: None
	// Purpose			: This will check if rapid fire is on, which will spawn 2 projectiles at once 
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void rapidFireAcitveChecker();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: movement()
	// Parameters		: None
	// Purpose			: To move the player based on the keys pressed and frame rate independently by using delta time and 
	//					,	lerping between the boudaries
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void movement();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: setAnimationToMoving()
	// Parameters		: None
	// Purpose			: This will set the animation state to moving, which is the default animation
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void setAnimationToMoving();

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: Player()
	// Parameters		: None
	// Notes			: As this is a default constructor it will initialise private variables
	//---------------------------------------------------------------------------------------------------------------------
	Player();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: Player()
	// Parameters		: None
	// Notes			: This destructor will delete all the pointers made
	//---------------------------------------------------------------------------------------------------------------------
	~Player();

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: initialise(AudioManager* pAudioManager , ProjectileManager* projectileManager , TextureManager* textureManager)
	// Parameters		: pAudioManager - This will play the player projectile sound
	//					, pProjectileManager - A passed through pointer of the projectile manager that has been made in the 
	//					,	Main Gamne
	//					: pTextureManager - A passed through pointer of the texture manager to set textures of the player 
	//					,	ship and projectiles
	// Purpose			: To use the passed through projectile manager instead of creating a new projectile manager so that 
	//					,	the program still uses a single instance of the projectile manager and to set the textures
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void initialise( AudioManager* pAudioManager , ProjectileManager* pProjectileManager , TextureManager* pTextureManager );
	
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: update(float deltaTime)
	// Parameters		: deltaTime - This will be used to make our movements smoother and frame rate independent
	// Purpose			: This overridden update function will update the movement of the player and firing a projectile
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void update(float deltaTime) override;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: render(sf::RenderTarget* targetWindow)
	// Parameters		: targetWindow - the window to render object to
	// Purpose			: To render the player's ship onto the screen
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void render(sf::RenderTarget* targetWindow) override;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setPlayer()
	// Parameters		: None
	// Purpose			: This will set the player for the new game to start
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setPlayer();

#pragma endregion

#pragma region getters and setters
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setIsPlayerAlive(bool isPlayerAlive)
	// Parameters		: isPlayerAlive - Whether or not the player is alive
	// Purpose			: To set the alive state of the player, which will mainly stop the main game to run
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void					setIsPlayerAlive( bool isPlayerAlive );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getIsPlayerAlive()
	// Parameters		: None
	// Purpose			: This will get to check if the player is alive or not
	// Returns			: A boolean whether the player is alive or not
	//---------------------------------------------------------------------------------------------------------------------
	const bool				getIsPlayerAlive() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getIsRespawning()
	// Parameters		: None
	// Purpose			: This will get to check if the player is respawning or not, which will disable the enemies dealing 
	//					,	damage to the player
	// Returns			: A boolean whether the player is alive or not
	//---------------------------------------------------------------------------------------------------------------------
	const bool				getIsRespawning() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setIsShieldEnabled(bool isShieldEnabled)
	// Parameters		: isShieldEnabled - Whether or not the player's sheild is active
	// Purpose			: To set the active state of player's shield, when the dasher hits the player it will disable the 
	//					,	shield when active
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void					setIsShieldEnabled( bool isShieldEnabled );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getIsShieldEnabled()
	// Parameters		: None
	// Purpose			: This will get to check if the player's shield is active or not
	// Returns			: A boolean whether the player is alive or not
	//---------------------------------------------------------------------------------------------------------------------
	const bool				getIsShieldEnabled()const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setHealthPoints(float healthPoints)
	// Parameters		: healthPoints - The desired amount of health points the player will have
	// Purpose			: To set the health points to player once it spawns
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void					setHealthPoints( float healthPoints );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getHealthPoints()
	// Parameters		: None
	// Purpose			: This will get player's current amount of health points they have, which will be used to display 
	//					,	on the health bar
	// Returns			: Current amount of health points
	//---------------------------------------------------------------------------------------------------------------------
	const float				getHealthPoints() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setPowerUpPoints(float powerUpPoints)
	// Parameters		: powerUpPoints - The desired amount of power up points the player will have
	// Purpose			: To set the power up points to player when the enemy dies
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void					setPowerUpPoints( float powerUpPoints );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getPowerUpPoints()
	// Parameters		: None
	// Purpose			: This will get player's current amount of power up points they have, which will be used to display 
	//					,	on the power up bar
	// Returns			: Current amount of power up points
	//---------------------------------------------------------------------------------------------------------------------
	const float				getPowerUpPoints() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getScore()
	// Parameters		: None
	// Purpose			: This will get player's current amount of lices, which will be used to display on the HUD
	// Returns			: Current amount of lives
	//---------------------------------------------------------------------------------------------------------------------
	const int				getLives() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setScore(int score)
	// Parameters		: score - The desired amount of score to be added
	// Purpose			: To set the score from when the enemy dies
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void					setScore( int score );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getScore()
	// Parameters		: None
	// Purpose			: This will get player's current score, which will be used to display on the HUD
	// Returns			: Current amount of score
	//---------------------------------------------------------------------------------------------------------------------
	const int				getScore() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getCircleCollider()
	// Parameters		: None
	// Purpose			: This will get the collision collider of the player, for collision detection
	// Returns			: The circle collider of the player
	//---------------------------------------------------------------------------------------------------------------------
	const CircleCollider&	getCircleCollider() const;

#pragma endregion
};

#endif // !PLAYER_H
