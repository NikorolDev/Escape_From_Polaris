#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include <vector>

#include "Object.h"
#include "ProjectileBase.h"

class TextureManager;

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: ProjectileManager
// Classes Inherited	: Object
// Purpose				: To handle every projectile instance that comes from the player and enemy, instead being handle 
//						,	in the player or enemy class
//-------------------------------------------------------------------------------------------------------------------------
class ProjectileManager : public Object
{
private:
#pragma region private variables
	int								m_maxAmountOfEnemyProjectiles; // The max amount of enemy projectile that is allowed in the game

	std::vector<ProjectileBase*>	m_projectiles; // A vector container of all projectiles in the game

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: ProjectileManager()
	// Parameters		: None
	// Notes			: As this is a default constructor will set the size of the vector for projectiles
	//---------------------------------------------------------------------------------------------------------------------
	ProjectileManager();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: ProjectileManager()
	// Parameters		: None
	// Notes			: This destructor will go through all projectiles in the vector and delete them
	//---------------------------------------------------------------------------------------------------------------------
	~ProjectileManager();

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: initialiseProjectiles(int maxAmountOfProjectiles , const ProjectileTypes& projectileType , TextureManager* pTextureManager);
	// Parameters		: maxAmountOfProjectiles - the maximum amount of projectiles needed to initialise of that type
	//					, projectileType - The type of projectile to initialise
	//					, pTextureManager - to set the texture of each projectile
	// Purpose			: This initialise function will initialise all projectiles based on the amount needed and set 
	//					,	textures to the each projectile
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void initialiseProjectiles( int maxAmountOfProjectiles , const ProjectileTypes& projectileType , TextureManager* pTextureManager );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: update(float deltaTime)
	// Parameters		: deltaTime - This will be used to pass the deltaTime to child classses of projectiles
	// Purpose			: This update function wil update all of the projectiles that are alive
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void update(float deltaTime) override;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: render(sf::RenderTarget* targetWindow)
	// Parameters		: targetWindow - the window to render object to
	// Purpose			: To loop through all projectiles that are alive to render them onto the screen
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void render(sf::RenderTarget* targetWindow) override;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: instantiateProjectile(const ProjectileTypes& projectileType)
	// Parameters		: projectileType - the type of projectile needed to instantiate
	// Purpose			: To instantiate a projectile of the type needed to spawn
	// Returns			: Return the projectile of that type
	//---------------------------------------------------------------------------------------------------------------------
	ProjectileBase* instantiateProjectile(const ProjectileTypes& projectileType);

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: clearProjectiles()
	// Parameters		: None
	// Purpose			: To clear projectiles off the screen, which will be used when starting a new game
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void clearProjectiles();
	
#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setMaxAmountOfEnemyProjectiles(int maxAmountOfEnemyProjectiles)
	// Parameters		: maxAmountOfEnemyProjectiles - the desired amount of enemy projectiles
	// Purpose			: This will set the max amount of enemy projectiles so more won't be created 
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setMaxAmountOfEnemyProjectiles( int maxAmountOfEnemyProjectiles );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getMaxAmountOfEnemyProjectiles()
	// Parameters		: None
	// Purpose			: This will get the maximum amount of enemy projectiles that will check if they've initialised
	//					,	already
	// Returns			: Max amount of enemy projectiles
	//---------------------------------------------------------------------------------------------------------------------
	const int getMaxAmountOfEnemyProjectiles() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getProjectiles()
	// Parameters		: None
	// Purpose			: This will get projectiles that are in the vector
	// Returns			: The whole vector container of projectiles
	//---------------------------------------------------------------------------------------------------------------------
	std::vector<ProjectileBase*>& getProjectiles();

#pragma endregion
};

#endif // !PROJECTILEMANAGER_H

