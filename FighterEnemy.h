#ifndef FIGHTERENEMY_H
#define FIGHTERENEMY_H

#include "EnemyBase.h"

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: FighterEnemy
// Classes Inherited	: EnemyBase
// Purpose				: To handle update the same way as the other enemies, but with the addition of shooting projectiles
//-------------------------------------------------------------------------------------------------------------------------
class FighterEnemy : public EnemyBase
{
private:
#pragma region private variables
	AudioManager*		m_pAudioManager; // This will be used to play a projectile sound when enemy shots their projectile
	ProjectileManager*	m_pProjectileManager; // This will be used to initialise enemy projectiles for fighter enemies

#pragma endregion

#pragma region private functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: shootProjectile()
	// Parameters		: None
	// Purpose			: The shooting of the enemy projectile from a picked fighter
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void shootProjectile();

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: FighterEnemy()
	// Parameters		: None
	// Notes			: As this is a default constructor it will initialise private variables
	//---------------------------------------------------------------------------------------------------------------------
	FighterEnemy();

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: initialise(AudioManager* pAudioManager ,Player* pPlayer , ProjectileManager* pProjectileManager , TextureManager* pTextureManager)
	// Parameters		: pAudioManager - this play the enemy projectile sound, when instantiated
	//					, pPlayer - passed through projectile manager, which wont be used in this enemy type so 
	//					,	it won't be stored
	//					, pProjectileManager - passed through projectile manager, which will be stored as it will 
	//					,	initialise enemy projectiles and instantiate them
	//					, pTextureManager - to pass texture manager, which won't be used in this class
	// Purpose			: This overridden initialise function will set the projectile manager during the initialisation
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void initialise( AudioManager* pAudioManager , Player* pPlayer , ProjectileManager* pProjectileManager , TextureManager* pTextureManager ) override;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: update(float deltaTime)
	// Parameters		: deltaTime - This will be used to make our movements smoother and frame rate independent
	// Purpose			: This overridden update function will update the fighter and shoot projectiles
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

#endif // !FIGHTERENEMY_H
