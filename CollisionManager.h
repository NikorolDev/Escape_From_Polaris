#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

// Forward class declarations of these classes 
class AudioManager;
class CircleCollider;
class EnemyManager;
class Player;
class ProjectileBase;
class ProjectileManager;

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: CollisionManager
// Classes Inherited	: None
// Purpose				: To manage every object's collision in the game
//-------------------------------------------------------------------------------------------------------------------------
class CollisionManager
{
private:
#pragma region private variables
	AudioManager*		m_pAudioManager; // This will play the scoring sound when the enemy is killed
	EnemyManager*		m_pEnemyManager; // Enemy manager to get the collider for each enemy
	ProjectileBase*		m_pEnemyProjectile; // This is to get the latest instantiated enemy projectile to collide with player's latest projectile
	Player*				m_pPlayer; // To get the collider for the player
	ProjectileBase*		m_pPlayerProjectile; // This is to get the latest instantiated player projectile to collide with enemy's latest projectile
	ProjectileManager*	m_pProjectileManager; // Projectile manager to get the collider for each projectile

#pragma endregion

#pragma region private functions

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: checkCircleColliderOverlap(const CircleCollider& circleCollider1, const CircleCollider& circleCollider2)
	// Parameters		: circleCollider1 - The first circle collider to check collision
	//					, circleCollider2 - The second circle collider to check collision
	// Purpose			: This will check if the 2 circles have overlaped
	// Returns			: A boolean that checks if the distance between the colliders is the same as the radius of both 
	//					,	circle colliders
	//---------------------------------------------------------------------------------------------------------------------
	bool checkCircleColliderOverlap(const CircleCollider& circleCollider1, const CircleCollider& circleCollider2);

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: calculateDistanceSquared(const sf::Vector2f positionDistanceDifference)
	// Parameters		: positionDistanceDifference - The position distance difference between 2 colliders
	// Purpose			: This calculate the distance between colliders and return a squared value of that 
	// Returns			: The distance difference between the 2 circle colliders
	//---------------------------------------------------------------------------------------------------------------------
	float calculateDistanceSquared(const sf::Vector2f positionDistanceDifference);

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: checkCollisionBetweenPlayerProjectilesAndEnemies(ProjectileBase* projectile)
	// Parameters		: projectile - Current projectile in the auto loop, which this function would get the player's projectile
	// Purpose			: This will check if a player projectile has collided with an enemy
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void checkCollisionBetweenPlayerProjectilesAndEnemies( ProjectileBase* projectile );

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: checkCollisionBetweenEnemyProjectilesAndPlayer( ProjectileBase* projectile )
	// Parameters		: projectile - Current projectile in the auto loop, which this function would need enemy's projectile
	// Purpose			: This will check if an enemy projectile has collided with the player
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void checkCollisionBetweenEnemyProjectilesAndPlayer( ProjectileBase* projectile );

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: checkCollisionBetweenEnemyProjectilesAndPlayerProjectiles( ProjectileBase* projectile )
	// Parameters		: projectile - Current projectile in the auto loop, which this function would need enemy's projectile and player's
	// Purpose			: This will check if an enemy projectile has collided with a player projectile
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void checkCollisionBetweenEnemyProjectilesAndPlayerProjectiles( ProjectileBase* projectile );

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: checkCollisionBetweenPlayerAndEnemy()
	// Parameters		: None
	// Purpose			: This will check if an enemy has collided with the player 
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void checkCollisionBetweenPlayerAndEnemy();

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: CollisionManager()
	// Parameters		: None
	// Notes			: This constructor will set the pointers to nullptr as they will be set by managers in the MainGame 
	//					,	class
	//---------------------------------------------------------------------------------------------------------------------
	CollisionManager();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: CollisionManager()
	// Parameters		: None
	// Notes			: This destructor will delete itself as no pointers are made on the heap
	//---------------------------------------------------------------------------------------------------------------------
	~CollisionManager();

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: initialise(AudioManager* pAudioManager , EnemyManager* pEnemyManager, Player* pPlayer, ProjectileManager* pProjectileManager)
	// Parameters		: pAudioManager - This will play the score sound when the enemy is killed
	//					, pEnemyManager - The enemy manager passed through enemy manager from the MainGame class
	//					, pPlayer - The player through from the MainGame class
	// 					, pProjectileManager - The projectile manager passed through enemy manager from the MainGame class
	// Purpose			: This will set all pointers that are nullptr from the constructor
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void initialise( AudioManager* pAudioManager , EnemyManager* pEnemyManager , Player* pPlayer , ProjectileManager* pProjectileManager );
	
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: update()
	// Parameters		: None
	// Purpose			: This updater will do all of the collision checks that will happen in the game
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void update();

#pragma endregion
	
};

#endif // !COLLISIONMANAGER_H
