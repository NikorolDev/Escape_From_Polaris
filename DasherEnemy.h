#ifndef DASHERENEMY_H
#define DASHERENEMY_H

#include "EnemyBase.h"

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: DasherEnemy
// Classes Inherited	: EnemyBase
// Purpose				: To update the same way as the other enemies, but with the addition of its own attack and 
//						,	properties
//-------------------------------------------------------------------------------------------------------------------------
class DasherEnemy : public EnemyBase
{
private:
#pragma region private variables
	bool			m_hasMissed; // This will check if the dasher has missed the player
	bool			m_isAttacking; // This will check if the dasher is attacking the player after its been charged up
	bool			m_isCharging; // This willc check if the dasher is charging their attack

	float			m_attackDelayTime; // The delay time before the dasher attacks
	float			m_deltaTime; // This will be used to increment all the timers and lerps in the class
	float			m_lerpToPlayerValue; // The lerp value from the dasher's formation position to the player
	float			m_lerpToFormationPositionValue; // The lerp value from the top off screen to the formation position

	Player*			m_pPlayer; // The player wil be used to get its position for the dasher to follow

#pragma endregion

#pragma region private functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: dasherAttack()
	// Parameters		: None
	// Purpose			: The dasher's unique attack, which is following the player until its charged, which will then dash 
	//					,	down at the player
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void dasherAttack();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: checkDeathState()
	// Parameters		: None
	// Purpose			: This will check if the dasher died, which will reset the dasher
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void checkDeathState();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: checkIfMissedThePlayer()
	// Parameters		: None
	// Purpose			: This will check if the dasher has missed the player, which will reset the dasher and return it to 
	//					,	its formation position
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void checkIfMissedPlayer();

#pragma endregion
public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: DasherEnemy()
	// Parameters		: None
	// Notes			: As this is a default constructor it will initialise private variables
	//---------------------------------------------------------------------------------------------------------------------
	DasherEnemy();

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: initialise(AudioManager* pAudioManager , Player* pPlayer , ProjectileManager* pProjectileManager , TextureManager* pTextureManager)
	// Parameters		: pAudioManager - there will be no sound played for dasher
	//					, pPlayer - passed through player that will be stored in this class as it is needed to make the 
	//					,	dasher follow the player before it attacks
	//					, pProjectileManager - passed through projectile manager, which wont be used in this enemy type so 
	//					,	it won't be stored
	//					, pTextureManager - to pass texture manager, which won't be used in this class
	// Purpose			: This overridden initialise function will set the player during the initialisation
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void initialise( AudioManager* pAudioManager , Player* pPlayer , ProjectileManager* pProjectileManager , TextureManager* pTextureManager ) override;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: update(float deltaTime)
	// Parameters		: deltaTime - This will be used to make movements smoother and frame rate independent and to 
	//					,	increment the lerp values
	// Purpose			: This overridden update function will update the dasher and initiate its attack and check if it's 
	//					,	dead or alive
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void update( float deltaTime ) override;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: reset()
	// Parameters		: None
	// Purpose			: This will reset the dasher by resetting necessary values, so that they are ready to used in the 
	//					,	next wave
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void reset() override;

#pragma endregion

};

#endif // !DASHERENEMY_H
