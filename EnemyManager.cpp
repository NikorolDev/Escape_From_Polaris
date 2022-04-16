#include <ctime>
#include <stdlib.h> 

#include "BiterEnemy.h"
#include "EnemyFormation.h"
#include "EnemyManager.h"
#include "DasherEnemy.h"
#include "FighterEnemy.h"
#include "Helpers.h"
#include "Player.h"
#include "TextureManager.h"

EnemyManager::EnemyManager()
// Setting these variables before the  constructor gets called
	: m_areAllEnemiesInFormation	( false )
	, m_hasBiterBeenPicked			( false )
	, m_hasDasherBeenPicked			( false )
	, m_isRespawningEnemies			( false )
	, m_deltaTime					( 0.0f )
	, m_shootingTime				( 0.0f )
	, m_biterAttackingID			( 0 )
	, m_dasherAttackingID			( 0 )
	, m_enemiesActive				( 0 )
	, m_numberOfBitersInWave		( 0 )
	, m_numberOfDashersInWave		( 0 )
	, m_numberOfFightersInWave		( 0 )
	, m_randomBiterID				( 0 )
	, m_randomDasherID				( 0 )
	, m_randomFighterID				( 0 )
	, m_pPlayer						( nullptr )
{
	// Create a new Enemy Formation class on the heap and set the other pointers to null as it's going to get passed through in the initialise function
	m_pEnemyFormation		= new EnemyFormation();

	// Set the size of the vector of the amount of enemies there will be in the game
	m_enemies.resize( Settings::EnemyProperties::c_maxAmountOfEnemies );
}

EnemyManager::~EnemyManager()
{
	// Go through the vector containing enemies and delete them from the heap
	for (auto& enemy : m_enemies)
	{
		safeDeletePointer( enemy );
	}
	
	// Delete enemy formation pointer
	safeDeletePointer( m_pEnemyFormation );
}

void EnemyManager::initialise( AudioManager* pAudioManager , TextureManager* pTextureManager, Player* pPlayer, ProjectileManager* pProjectileManager )
{
	// Set the player pointer
	m_pPlayer = pPlayer;

	// Create a counter to count all of the enemies so that it will be easy to initialise the correct amount of each enemy type
	int counter = 0;

	// Go through the vector of enemies
	for ( auto& enemy : m_enemies )
	{
		// If enemy does not exist
		if ( enemy == nullptr )
		{
			// Check if the counter is less than max of each type which is 20. Which means there will 20 enemies of each type in the game
			if ( counter < Settings::EnemyProperties::c_maxAmountOfEachEnemyTypes )
			{
				// Create a new biter enemy, assign ists texture and update the count of biters
				enemy = new BiterEnemy();
				enemy->loadSpriteTexture( pTextureManager->getTexture( GameTextures::BiterEnemyTexture ) , true );
			}

			// Check if the counter is between 20 and 39
			if ( counter >= Settings::EnemyProperties::c_maxAmountOfEachEnemyTypes &&
				counter < ( Settings::EnemyProperties::c_maxAmountOfEachEnemyTypes * 2 ) )
			{
				// Create a new dasher enemy
				enemy = new DasherEnemy();
				enemy->loadSpriteTexture( pTextureManager->getTexture( GameTextures::DasherEnemyTexture ) , true );
			}

			// Check if the counter is between 40 and 59
			if ( counter >= ( Settings::EnemyProperties::c_maxAmountOfEachEnemyTypes * 2 ) &&
				counter < ( Settings::EnemyProperties::c_maxAmountOfEachEnemyTypes * 3 ) )
			{
				// Create a new fighter enemy
				enemy = new FighterEnemy();
				enemy->loadSpriteTexture( pTextureManager->getTexture( GameTextures::FighterEnemyTexture ) , true );
			}

			// Initialise enemy by also passing these values
			enemy->initialise( pAudioManager , pPlayer , pProjectileManager , pTextureManager );

			// Increment the counter
			counter++;
		}
	}
}

void EnemyManager::update(float deltaTime)
{
	// Set the delta time with the elapsed time passed through
	m_deltaTime = deltaTime;

	// Go through all enemies in the vector container
	for (auto& enemy : m_enemies)
	{
		// Check if the current enemy exists, if it's alive 
		if ( enemy != nullptr && 
			 enemy->getIsEnemyAlive() == true )
		{
			// Call the update function of that enemy
			enemy->update( deltaTime );
		}
	}

	// Check if all enemies are in formation
	if ( m_areAllEnemiesInFormation == false )
	{
		// If not then move enemies to their formations
		moveEnemiesToFormation();
	}
	else
	{
		// Check if all enemies are dead
		checkIfAllEnemiesDied();

		// Check if they are not respawning 
		if ( m_isRespawningEnemies == false )
		{
			// Allow enemies to attack by picking a random enemy to attack for each type
			pickBiterEnemyToAttack();
			pickFighterEnemyToShoot();
			pickDasherEnemyToAttack();
		}
	}
}

void EnemyManager::render(sf::RenderTarget* targetWindow)
{
	// Go through all enemies in the vector
	for (auto& enemy : m_enemies)
	{
		// Check if the current enemy exits and it it's alive
		if ( enemy != nullptr && enemy->getIsEnemyAlive() == true )
		{
			// Render the enemy onto the window
			enemy->render( targetWindow );
		}
	}
}

void EnemyManager::resetEnemies()
{
	// Set enemies active to 0
	m_enemiesActive = 0;

	// Set that enemies are respawning
	m_isRespawningEnemies = true;

	// Reset the values for each enemy that is used in the is class
	m_areAllEnemiesInFormation	= false;
	m_hasBiterBeenPicked		= false;
	m_hasDasherBeenPicked		= false;
	m_shootingTime				= 0.0f;
	m_randomBiterID				= 0;
	m_randomDasherID			= 0;
	m_biterAttackingID			= 0;
	m_dasherAttackingID			= 0;
	m_numberOfBitersInWave		= 0;
	m_numberOfDashersInWave		= 0;
	m_numberOfFightersInWave	= 0;

	// Loop through every enemy and reset their values for the next wave
	for ( auto& enemy : m_enemies )
	{
		if ( enemy != nullptr )
		{
			enemy->setIsEnemyAlive( false );
			enemy->reset();
		}
	}

	// If the player is dead then re-initialise the first wave, when the game restarts
	if ( m_pPlayer->getIsPlayerAlive() == false )
	{
		m_pEnemyFormation->setHasFirstWaveInitiated( false );
	}

	// Spawn enemies
	spawnEnemies();
}

void EnemyManager::spawnEnemies()
{
	// To spawn enemies, initialise formation first which will read a csv file and put the value in a 2D array
	m_pEnemyFormation->initialiseNewFormation( );

	// Make a float to loop through position y and another float for formation offest, which is a value that will move the enemies to their positions on screen
	float formationPositionY = Settings::EnemyProperties::c_formationPositionY;
	float formationOffsetX = 0.0f;

	// These floats are the spawn positions for enemies, which will be off the screen on the left and right. Using this, a formation position for each enemy can be made for a spawning animaiton
	float leftSpawnPositionX = Settings::EnemyProperties::c_spawnLeftPoisitionX;
	float rightSpawnPositionX = Settings::EnemyProperties::c_spawnRightPoisitionX;

	// Make these integers to represent each enemy in the vector container, so that the correct enemy is used
	int biterCounter	= 0;
	int dasherCounter	= Settings::EnemyProperties::c_maxAmountOfEachEnemyTypes;
	int fighterCounter	= Settings::EnemyProperties::c_maxAmountOfEachEnemyTypes * 2;

	// A spawn position that is modifiable to be looped and to set each enemy in the formation thier spawn position, which will be off the screen
	sf::Vector2f spawnPosition = sf::Vector2f( 0 , formationPositionY );

	// Go through each row in a formation
	for ( int formationRow = 0; formationRow < Settings::EnemyProperties::c_formationHeight; ++formationRow )
	{
		// Go through each column in a formaiton
		for ( int formationColumn = 0; formationColumn < Settings::EnemyProperties::c_formationWidth; ++formationColumn )
		{
			// If the enemy can still spawn on the left side off the screen
			if ( leftSpawnPositionX < Settings::EnemyProperties::c_maxSpawningLeftPositionX )
			{
				spawnPosition = sf::Vector2f( leftSpawnPositionX , formationPositionY ); // Set the spawn position on the left side of the off screen
				formationOffsetX = Settings::EnemyProperties::c_leftFromationOffsetX; // Set the formation formation offset so the enemy can move to the formation position
				leftSpawnPositionX += Settings::EnemyProperties::c_spawningPositionXIncrementor; // Increment the spawning position X
			}
			// If the enemy can spawn not too far away from the screen
			else if ( rightSpawnPositionX <= Settings::EnemyProperties::c_maxSpawningRightPositionX )
			{
				spawnPosition = sf::Vector2f( rightSpawnPositionX , formationPositionY ); // Set the spawn position on the right side of the of screen
				formationOffsetX = Settings::EnemyProperties::c_rightFromationOffsetX; // Set the formation position offset
				rightSpawnPositionX += Settings::EnemyProperties::c_spawningPositionXIncrementor; // Increment the spawn position X
			}

			// Pick an enemy based on position in the formation in the csv file
			switch ( m_pEnemyFormation->getEnemyFormationElement( formationRow , formationColumn ) )
			{
				// Based on the enemy in the formation array, it will spawn the enemy by passsing through the spawn position, formaiton position and set it to be alive
				// Using the counter it will get the enemy in the vector container 
				case 1: // Biter enemy
				{
					m_enemies.at( biterCounter )->spawnEnemy( spawnPosition , sf::Vector2f( spawnPosition.x + formationOffsetX , spawnPosition.y ) );
					m_numberOfBitersInWave++;
					m_enemiesActive++;
					biterCounter++;
					break;
				}

				case 2: // Fighter enemy
				{
					m_enemies.at( fighterCounter )->spawnEnemy( spawnPosition , sf::Vector2f( spawnPosition.x + formationOffsetX , spawnPosition.y ) );
					m_numberOfFightersInWave++;
					m_enemiesActive++;
					fighterCounter++;
					break;
				}

				case 3: // Dasher enemy
				{
					m_enemies.at( dasherCounter )->spawnEnemy( spawnPosition , sf::Vector2f( spawnPosition.x + formationOffsetX , spawnPosition.y ) );
					m_numberOfDashersInWave++;
					m_enemiesActive++;
					dasherCounter++;
					break;
				}

				default: { break; }
			}
		}

		// Once the column is done, it will set back the left and right spawn position to their starting values and increment the formation position Y
		leftSpawnPositionX = Settings::EnemyProperties::c_spawnLeftPoisitionX;
		rightSpawnPositionX = Settings::EnemyProperties::c_spawnRightPoisitionX;
		formationPositionY += 80.0f;
	}
}

void EnemyManager::moveEnemiesToFormation()
{
	// Go through the formation size which is the width and height of the formation
	for ( int enemyCounter = 0; enemyCounter < Settings::EnemyProperties::c_maxAmountOfEnemies; ++enemyCounter )
	{
		// Check if the enemy exists and that it is alive
		if ( m_enemies.at( enemyCounter ) != nullptr && m_enemies.at( enemyCounter )->getIsEnemyAlive() == true )
		{
			// If every enemy is not in formation 
			if ( m_enemies.at( enemyCounter )->getIsInFomation() == false )
			{
				// Move the enemy to their formation
				m_enemies.at( enemyCounter )->setCanEnemyMoveToFormation( true );				
			}
			// If each enemy is in formation
			else 
			{
				m_areAllEnemiesInFormation = true; // This bool will stop the enemies from goin to their formation position
				m_isRespawningEnemies = false;
			}
		}
	}
}

void EnemyManager::pickBiterEnemyToAttack()
{
	// If the biter enemy is not attacking and if there are any biters
	if ( m_hasBiterBeenPicked == false && 
		 m_numberOfBitersInWave > 0 )
	{
		// Pick a random biter enemy
		m_randomBiterID = randomiseEnemy( m_numberOfBitersInWave , 0 );

		// Check if the random selected enemy is a biter
		if ( m_enemies.at( m_randomBiterID )->getEnemyType() == EnemyTypes::Biter )
		{
			// Check if that biter is alive
			if ( m_enemies.at( m_randomBiterID )->getIsEnemyAlive() == true )
			{
				// Assign biter attacking ID from randomly picked biter
				m_biterAttackingID = m_randomBiterID;				
			}

			// If the rnadomised biter is dead
			else 
			{
				// Loop through all biters that are in the wave
				for ( int biterAliveCounter = 0; biterAliveCounter < m_numberOfBitersInWave; ++biterAliveCounter )
				{
					// Check if the biter in the counter is alive
					if ( m_enemies.at( biterAliveCounter )->getIsEnemyAlive() == true )
					{
						// Assign biter attacking ID from the loop
						m_biterAttackingID = biterAliveCounter;
						break;
					}
				}
			}
			
			// Set biter to attack and so it cant pick another biter until they miss or die
			m_enemies.at( m_biterAttackingID )->setCanEnemyAttack( true );
			m_hasBiterBeenPicked = true;
		}
	}

	// Check if the player can not attack, which would be if they died
	if ( m_enemies.at( m_biterAttackingID )->getCanEnemyAttack() == false )
	{
		// Allow to pick another biter to attack
		m_hasBiterBeenPicked = false;
	}
}

void EnemyManager::pickFighterEnemyToShoot()
{
	// Increment the shooting time by deltaTime, so there is a time difference before the fight er enemy shoots
	m_shootingTime += m_deltaTime;

	// If the shooting time is above the shooting rate, which is the time to shoot
	if ( m_shootingTime > Settings::EnemyProperties::FighterProperties::c_shootingRate && 
		 m_numberOfFightersInWave > 0 )
	{
		// Pick a fighter enemy that is alive
		m_randomFighterID = randomiseEnemy( m_numberOfFightersInWave ,  Settings::EnemyProperties::c_maxAmountOfEachEnemyTypes * 2  );

		// Check if that randomly picked enemy is a fighter
		if ( m_enemies.at( m_randomFighterID )->getEnemyType() == EnemyTypes::Fighter )
		{
			// Check if its alive
			if ( m_enemies.at( m_randomFighterID )->getIsEnemyAlive() == true )
			{
				// Shoot a projectile from a randomly picked enemy
				m_enemies.at( m_randomFighterID )->setCanEnemyAttack( true );
				m_shootingTime = 0;
			}
			else // if the randomly picked enemy is not alive
			{
				// Loop through all fighters that are in the current wave, which will get the first fighter that is currently alive
				for ( int fighterAliveCounter = ( Settings::EnemyProperties::c_maxAmountOfEachEnemyTypes * 2 ); fighterAliveCounter < ( Settings::EnemyProperties::c_maxAmountOfEachEnemyTypes * 2 ) + m_numberOfFightersInWave; ++fighterAliveCounter )
				{
					// Check if that fighter is alive
					if ( m_enemies.at( fighterAliveCounter )->getIsEnemyAlive() == true )
					{
						// Shoot a projectile from that enemy, reset shooting time and break the loop 
						m_enemies.at( fighterAliveCounter )->setCanEnemyAttack( true );
						m_shootingTime = 0;
						break;
					}
				}
			}
		}
	}
}

void EnemyManager::pickDasherEnemyToAttack()
{
	// Check if a dasher enemy is attacking
	if ( m_hasDasherBeenPicked == false && 
		 m_numberOfDashersInWave > 0 )
	{
		// Pick a random dasher by using the amount of dashers in the wave and the minimum range starting from 20
		m_randomDasherID = randomiseEnemy( m_numberOfDashersInWave , Settings::EnemyProperties::c_maxAmountOfEachEnemyTypes );

		// Check if the randomly picked enemy is a dasher
		if ( m_enemies.at( m_randomDasherID )->getEnemyType() == EnemyTypes::Dasher )
		{
			// Check if the dasher is alive
			if ( m_enemies.at( m_randomDasherID )->getIsEnemyAlive() == true )
			{
				// Assign the attacking dasher ID
				m_dasherAttackingID = m_randomDasherID;
			}
			else // if randomly picked dasher is not alive
			{
				// Loop through all dashers that in the current wave
				for ( int dasherAliveCounter = Settings::EnemyProperties::c_maxAmountOfEachEnemyTypes; dasherAliveCounter < Settings::EnemyProperties::c_maxAmountOfEachEnemyTypes + m_numberOfDashersInWave; ++dasherAliveCounter )
				{
					// Check if the curent dasher is alive
					if ( m_enemies.at( dasherAliveCounter )->getIsEnemyAlive() == true )
					{
						// Assign the attacking dasher ID
						m_dasherAttackingID = dasherAliveCounter;
					}
				}
			}

			// Set dasher to attack and so it cant pick another dasher until they miss or die
			m_enemies.at( m_dasherAttackingID )->setCanEnemyAttack( true );
			m_hasDasherBeenPicked = true;
		}
	}

	// Check if the enemy is not attacking anymore
	if ( m_enemies.at( m_dasherAttackingID )->getCanEnemyAttack() == false )
	{
		// Allow the next dasher to be picked
		m_hasDasherBeenPicked = false;
	}
}

int EnemyManager::randomiseEnemy( int numberOfEnemyTypeAlive , int minRange )
{
	// Initialise random number generator
	srand( ( int ) time( 0 ) );

	// Return the random from the amount of enemies alive and add the minimum range, which is the starting IDs
	return ( rand() % numberOfEnemyTypeAlive ) + minRange;
}

void EnemyManager::checkIfAllEnemiesDied()
{
	// Check if all enemies are dead if none are active
	if ( m_enemiesActive == 0 )
	{		
		// Reset enemies
		resetEnemies();
	}
}

void EnemyManager::setEnemiesActive( int enemiesActive )	{ m_enemiesActive = enemiesActive; }

const int EnemyManager::getEnemiesActive() const			{ return m_enemiesActive; }

std::vector<EnemyBase*>& EnemyManager::getEnemies()			{ return m_enemies; }
