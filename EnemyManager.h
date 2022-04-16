#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <SFML/System/Clock.hpp>
#include <vector>

#include "EnemyBase.h"
#include "Object.h"

//Forward class declaration of ProjectileManager to resolve circular includes and to set a pointer of that class
class AudioManager;
class EnemyFormation;
class Player;
class ProjectileManager;
class TextureManager;

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: EnemyManager
// Classes Inherited	: Object
// Purpose				: To handle every enemy in this class, by updating, rendering and pick which to attack
//-------------------------------------------------------------------------------------------------------------------------
class EnemyManager : public Object
{
private:
#pragma region private variables
	bool					m_areAllEnemiesInFormation; // This will check if all enemies are in formation positions
	bool					m_hasBiterBeenPicked; // This will check if a biter has been picked to attack
	bool					m_hasDasherBeenPicked; // This will check if a dasher has been picked to attack
	bool					m_isRespawningEnemies; // This will check if an enemy is respawning

	float					m_deltaTime; // This will be passed to enemy classes and for timers such as the shooting tiem
	float					m_shootingTime; // This is the current time that will be checked if the fighter can shoot

	int						m_biterAttackingID; // The index of the biter attacking
	int						m_dasherAttackingID; // The index of the dasher attacking
	int						m_enemiesActive; // The number of enemies active in the wave
	int						m_numberOfBitersInWave; // The number of biters in the wave
	int						m_numberOfDashersInWave; // The number of dashers in the wave
	int						m_numberOfFightersInWave; // The number of fighters in the wave
	int						m_randomBiterID; // The randomised biter picked for attacking
	int						m_randomDasherID; // The randomised dasher picked for attacking
	int						m_randomFighterID; // The randomised fighter picked for attacking

	std::vector<EnemyBase*> m_enemies; // The container that stores all enemies

	EnemyFormation*			m_pEnemyFormation; // Pointer to the enemy formation, that will generate formations for the enemies
	Player*					m_pPlayer; // Pointer to the player which will check if the player is dead for re-initialising the first wave

#pragma endregion

#pragma region private functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: spawnEnemies()
	// Parameters		: None
	// Purpose			: This will spawn all of the enemies from the formation into their positions and give them 
	//					,	formation positions
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void spawnEnemies();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: moveEnemiesToFormation()
	// Parameters		: None
	// Purpose			: This will move enemies to their fomrations and check if they are all in formation to allow 
	//					,	enemies to attack
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void moveEnemiesToFormation();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: pickBiterEnemyToAttack()
	// Parameters		: None
	// Purpose			: This will pick a biter enemy to attack, whether it was randomised or first in the index that is 
	//					,	alive
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void pickBiterEnemyToAttack();
		
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: pickFighterEnemyToShoot()
	// Parameters		: None
	// Purpose			: This will pick a fighter enemy to attack, whether it was randomised or first in the index that is 
	//					,	alive
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void pickFighterEnemyToShoot();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: pickDasherEnemyToAttack()
	// Parameters		: None
	// Purpose			: This will pick a dashter enemy to attack, whether it was randomised or first in the index that is 
	//					,	alive
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void pickDasherEnemyToAttack();
	
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: checkIfAllEnemiesDied()
	// Parameters		: None
	// Purpose			: This check if all enemies have died, which will reset the values and spawn next wave of enemies
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void checkIfAllEnemiesDied();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: randomiseEnemy()
	// Parameters		: numberOfEnemyTypeAlive - number of that enemy type is alive
	//					, minRange - minum range, which would be the starting index of that enemy
	// Purpose			: This will randomise enemies of the type and using the amount that are in the wave that will 
	//					,	attack
	// Returns			: Return a randomised index for enemy type
	//---------------------------------------------------------------------------------------------------------------------
	int randomiseEnemy( int numberOfEnemyTypeAlive , int minRange );

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: EnemyManager()
	// Parameters		: None
	// Notes			: As this is a default constructor will create a new enemy formation class and set the size of the 
	//					,	vector for enemies
	//---------------------------------------------------------------------------------------------------------------------
	EnemyManager();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: EnemyManager()
	// Parameters		: None
	// Notes			: This destructor will go through all enemies in the vector and delete them and delete the enemy 
	//					,	formation
	//---------------------------------------------------------------------------------------------------------------------
	~EnemyManager();

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: initialise(AudioManager* pAudioManager , TextureManager* pTextureManager , Player* pPlayer , ProjectileManager* pProjectileManager)
	// Parameters		: pAudioManager - to allow enemies to play sounds
	//					, pTextureManager - to set the texture of each enemy during initialisation
	//					, pPlayer - passed through player for enemies that need it and to be checked for alive state
	//					, pProjectileManager - passed through projectile manager for enemies that need it
	// Purpose			: This initialise function will initialise all enemies and set textures to the each enemy
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void initialise( AudioManager* pAudioManager , TextureManager* pTextureManager , Player* pPlayer , ProjectileManager* pProjectileManager );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: update(float deltaTime)
	// Parameters		: deltaTime - This will be used to pass the deltaTime to child classses and used as a timer for 
	//					,	fighter shoooting
	// Purpose			: This update function wil update all of the enemies, pick random enemies to attack and check if 
	//					,	all enemies are dead
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void update( float deltaTime ) override;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: render(sf::RenderTarget* targetWindow)
	// Parameters		: targetWindow - the window to render object to
	// Purpose			: To loop through all enemies that are alive to render them onto the screen
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void render( sf::RenderTarget* targetWindow );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: resetEnemies()
	// Parameters		: None
	// Purpose			: This will reset the values in this manager and reset every enemy in the vector
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void resetEnemies();

#pragma endregion

#pragma region getters and setters
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setEnemiesActive()
	// Parameters		: enemiesActive - the desired amount of enemies currently active
	// Purpose			: This will set the amount of enemies active. Mainly to decremnt enemies active in the collision 
	//					,	manager
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setEnemiesActive( int enemiesActive );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getEnemiesActive()
	// Parameters		: None
	// Purpose			: This will get the amount of enemies currently active
	// Returns			: Current amount of enmeis active
	//---------------------------------------------------------------------------------------------------------------------
	const int getEnemiesActive() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getEnemies()
	// Parameters		: None
	// Purpose			: This will get enemies that are in the vector
	// Returns			: The whole vector container of enemies
	//---------------------------------------------------------------------------------------------------------------------
	std::vector<EnemyBase*>& getEnemies();
};

#endif // !ENEMYMANAGER_H
