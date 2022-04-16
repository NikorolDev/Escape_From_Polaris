#ifndef ENEMYBASE_H
#define ENEMYBASE_H

#include "CircleCollider.h"
#include "SpriteObject.h"

// Forward class declarations for player and projectile manager
class AudioManager;
class Player;
class ProjectileManager;
class TextureManager;

// Types of enemies that are in the game
enum class EnemyTypes
{
	Biter,
	Dasher,
	Fighter,
	BlankEnemy,
};

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: EnemyBase
// Classes Inherited	: SpriteObject
// Purpose				: To handle every single enemy in this base class, such as health handling and moving to formaitons
//-------------------------------------------------------------------------------------------------------------------------
class EnemyBase : public SpriteObject
{
private:
#pragma region private variables
	bool			m_canAttack; // This will check if the enemy can attack the player
	bool			m_canMoveToFormation; // This will check if the enemy can move towards their formation position
	bool			m_isInFormation; // This will check if the enemy is in their formation position
	bool			m_isAlive; // This will check if the enemy is alive or not

	float			m_damage; // This is the amount damage the enemy will deal to the player
	float			m_healthPoints; // This is the amount of health points the enemy will have
	float			m_movementToFormationTime; // This is the movement formation time, which is a lerp value
	float			m_speed; // The speed that the enemy will travel

	CircleCollider	m_circleCollider; // The circle collider for hit detections

	EnemyTypes		m_enemyType; // Types of enemies to set for each enemy in the game

	sf::Vector2f	m_spawningPosition; // Spawning position, which will be off the screen
	sf::Vector2f	m_formationPosition; // Formation position, which will be on screen

#pragma endregion

#pragma region private function
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: moveToFormationPosition(float deltaTime)
	// Parameters		: deltaTime - to lerp all enemies into their formation positions
	// Purpose			: This will move every enemy that is alive into their formation positions, whcih if they all are, 
	//					,	it will allow enemies to attack
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void moveToFormationPosition(float deltaTime);

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: EnemyBase()
	// Parameters		: None
	// Notes			: As this is a default constructor it will initialise private variables
	//---------------------------------------------------------------------------------------------------------------------
	EnemyBase();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: EnemyBase()
	// Parameters		: None
	// Notes			: This destructor will delete itself and as it is virtual it will delete the child classes as well
	//---------------------------------------------------------------------------------------------------------------------
	virtual ~EnemyBase() {};

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: initialise( AudioManager* pAudioManager, Player* pPlayer , ProjectileManager* pProjectileManager , TextureManager* pTextureManager)
	// Parameters		: pAudioManager - to allow enemies to play sounds
	//					, pPlayer - passed through player that will be stored in child classes that need it
	//					, pProjectileManager - passed through projectile manager that will be stored in child classes that
	//					,	need it
	//					, pTextureManager - to pass texture manager, which won't be used in this class
	// Purpose			: This initialise function will only be used for child classes that need these passed classes
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void initialise( AudioManager* pAudioManager , Player* pPlayer , ProjectileManager* pProjectileManager , TextureManager* pTextureManager ) {};

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: update(float deltaTime)
	// Parameters		: deltaTime - This will be used to pass the deltaTime to child classses and be for lerping to 
	//					,	formation position
	// Purpose			: This update function mainly check if all enemies are alive
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void update(float deltaTime) override;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: render(sf::RenderTarget* targetWindow)
	// Parameters		: targetWindow - the window to render object to
	// Purpose			: To render the every enemy that are alive onto the screen
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void render(sf::RenderTarget* targetWindow) override;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: reset()
	// Parameters		: None
	// Purpose			: This will reset every enemy's properties that are set, such as spawning positions and 
	//					,	formation positions
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void reset();

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: spawnEnemy(const sf::Vector2f& spawnPosition , const sf::Vector2f& formaitonPosition)
	// Parameters		: spawnPosition - the spawning position of the enemy
	//					: formaitonPosition - the formation position of the enemy
	// Purpose			: This will spawn set the positions of spawning and formation and set the enemy's alive state
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void spawnEnemy( const sf::Vector2f& spawnPosition , const sf::Vector2f& formaitonPosition );

#pragma endregion

#pragma region getters and setters
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setEnemyType(const EnemyTypes enemyType)
	// Parameters		: enemyType - the type of the enemy will be
	// Purpose			: This will set the enemy type so it can be recognised and not mistaken by another enemy
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setEnemyType( const EnemyTypes enemyType );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getEnemyType()
	// Parameters		: None
	// Purpose			: This will get the enemy type so it can be recognised and allow it to attack, or check for 
	//					,	specific collision detection with that enemy
	// Returns			: Get the enemy type that the game wants to recognise
	//---------------------------------------------------------------------------------------------------------------------
	const EnemyTypes& getEnemyType() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setCanEnemyAttack(bool canAttack)
	// Parameters		: canAttack - Whether or not the picked enemy to attack
	// Purpose			: This will set the picked enemy from the enemy manager to attack
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setCanEnemyAttack( bool canAttack );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getCanEnemyAttack()
	// Parameters		: None
	// Purpose			: This will get to check if the enemy can attack
	// Returns			: A boolean whether the enemy is attacking or not
	//---------------------------------------------------------------------------------------------------------------------
	const bool getCanEnemyAttack() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setCanEnemyMoveToFormation(bool canMoveToFormation)
	// Parameters		: canMoveToFormation - Whether or not the enemy can move to their formation position
	// Purpose			: To allow enemies to their formation positions
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setCanEnemyMoveToFormation( bool canMoveToFormation );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setIsEnemyAlive(bool isAlive)
	// Parameters		: isAlive - Whether or not the enemy is alive
	// Purpose			: To set the alive state of the enemy, which will allow them to function
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setIsEnemyAlive( bool isAlive );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getIsEnemyAlive()
	// Parameters		: None
	// Purpose			: This will get to check if the enemy is alive or not
	// Returns			: A boolean whether the enemy is alive or not
	//---------------------------------------------------------------------------------------------------------------------
	const bool getIsEnemyAlive() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getIsInFomation()
	// Parameters		: None
	// Purpose			: This will get to check if the enemy is in formation position
	// Returns			: A boolean whether the enemy is in their position
	//---------------------------------------------------------------------------------------------------------------------
	const bool getIsInFomation() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setDamageAmount(float damageAmount)
	// Parameters		: damageAmount - The desired amount of damage the enemy will deal to the player
	// Purpose			: To set the damage that the enemy will deal to when overlapping with the player for example
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setDamageAmount( float damageAmount );
	
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getDamageAmount()
	// Parameters		: None
	// Purpose			: This will get the damage amount the enemy deals to be used in collision detection with the player 
	//					,	for example
	// Returns			: Amount of damage that will be dealt
	//---------------------------------------------------------------------------------------------------------------------
	const float getDamageAmount() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setHealthPoints(float healthPoints)
	// Parameters		: healthPoints - The desired amount of health points the enemy will have
	// Purpose			: To set the health points to enemy once they spawn
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setHealthPoints( float healthPoints );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getHealthPoints()
	// Parameters		: None
	// Purpose			: This will get their current amount of health points they have, which will be used for checking if 
	//					,	they have to stay alive
	// Returns			: Current amount of health points
	//---------------------------------------------------------------------------------------------------------------------
	const float getHealthPoints() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setSpeed(float speed)
	// Parameters		: speed - The desired speed the enemy will travel by
	// Purpose			: To set the speed, whether it will be constant or changeable for the enemy to move around the map
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setSpeed( float speed );
	
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getSpeed()
	// Parameters		: None
	// Purpose			: This will get the current speed the enemy is travelling by
	// Returns			: The current speed of the enemy
	//---------------------------------------------------------------------------------------------------------------------
	const float getSpeed() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getFormationPosition()
	// Parameters		: None
	// Purpose			: This will get the formation position for the enemies. Mainly used for enemies that miss the 
	//					,	player, they will go back to it
	// Returns			: The formation position of the enemy
	//---------------------------------------------------------------------------------------------------------------------
	const sf::Vector2f& getFormationPosition() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getCircleCollider()
	// Parameters		: None
	// Purpose			: This will get the collision collider of the enemy, for collision detection
	// Returns			: The circle collider of the enemy
	//---------------------------------------------------------------------------------------------------------------------
	 CircleCollider& getCircleCollider();

 #pragma endregion

};

#endif // !ENEMYBASE_H
