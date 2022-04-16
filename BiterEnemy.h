#ifndef BITERENEMY_H
#define BITERENEMY_H

#include "EnemyBase.h"

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: BiterEnemy
// Classes Inherited	: EnemyBase
// Purpose				: To handle update the same way as the other enemies, but with the addition of its own attack and 
//						,	properties
//-------------------------------------------------------------------------------------------------------------------------
class BiterEnemy : public EnemyBase
{
private:
#pragma region private variables
	bool			m_hasMissed; // This will check if the biter has missed the player

	float			m_deltaTime; // This the time that will be used to update the biter frame rate indepently
	float			m_lerpFormationPosition; // This is the lerp position between the position above the screen and its formation position

	Player*			m_pPlayer; // This is will be used to get player's position in order to set the centreline

	sf::Vector2f	m_centreline; // This is player's position used as a centreline of the sine wave

#pragma endregion

#pragma region private functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: biterAttack()
	// Parameters		: None
	// Purpose			: The biter's unique attack, which is homing around the player in a sine wave motion
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void biterAttack();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: checkDeathState()
	// Parameters		: None
	// Purpose			: This will check if the biter died, which will reset the biter
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void checkDeathState();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: checkIfMissedThePlayer()
	// Parameters		: None
	// Purpose			: This will check if the biter has missed the player, which will reset the biter and return it to 
	//					,	its formation position
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void checkIfMissedThePlayer();

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: BiterEnemy()
	// Parameters		: None
	// Notes			: As this is a default constructor it will initialise private variables
	//---------------------------------------------------------------------------------------------------------------------
	BiterEnemy();

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: initialise( AudioManager* pAudioManager Player* pPlayer , ProjectileManager* pProjectileManager , TextureManager* pTextureManager)
	// Parameters		: pAudioManager - there will be no sound played for biter
	//					, pPlayer - passed through player that will be stored in this class as it is needed to set the 
	//					,	centreline of sine wave
	//					, pProjectileManager - passed through projectile manager, which wont be used in this enemy type so 
	//					,	it won't be stored
	//					, pTextureManager - to pass texture manager, which won't be used in this class
	// Purpose			: This overridden initialise function will set the player during the initialisation
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void initialise( AudioManager* pAudioManager , Player* pPlayer , ProjectileManager* pProjectileManager , TextureManager* pTextureManager ) override;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: update(float deltaTime)
	// Parameters		: deltaTime - This will be used to make movements smoother and frame rate independent
	// Purpose			: This overridden update function will update the biter and initiate its attack and check if it's 
	//					,	dead or alive
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void update( float deltaTime ) override;
	
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: reset()
	// Parameters		: None
	// Purpose			: This will reset the biter by resetting necessary values, so that they are ready to used in the 
	//					,	next wave
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void reset() override;

#pragma endregion

};

#endif // !BITERENEMY_H
