#ifndef PROJECTILEBASE_H
#define PROJECTILEBASE_H

#include "CircleCollider.h"
#include "SpriteObject.h"

// Types of projectiles that are in the game
enum class ProjectileTypes
{
	DefaultProjectile,
	EnemyProjectile,
	PlayerProjectile,
	PlayerRapidProjectile
};

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: ProjectileBase
// Classes Inherited	: SpriteObject
// Purpose				: To handle every enemy in this class, by updating, rendering and pick which to attack
//-------------------------------------------------------------------------------------------------------------------------
class ProjectileBase : public SpriteObject
{
private:
#pragma region private variables
	bool m_isAlive; //This will check if the projectile is still alive

	float m_damage; // The damage that the projectile will deal
	float m_speed; //The speed of the projectile will travel;

	CircleCollider m_circleCollider; // The circle collider that will allow collision to happen with other objects
	ProjectileTypes m_projectileType; // The types of projectile to set for each projectile in the game

	sf::Vector2f m_direction; //The direction that the projectile will travel

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: ProjectileBase()
	// Parameters		: None
	// Notes			: This constructor will initialise all the variables to 0
	//---------------------------------------------------------------------------------------------------------------------
	ProjectileBase();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: ProjectileBase()
	// Parameters		: None
	// Notes			: This destructor will delete itself as no pointers will be initialised and its child classes
	//---------------------------------------------------------------------------------------------------------------------
	virtual ~ProjectileBase() {};

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: update()
	// Parameters		: None
	// Purpose			: To update the projectile, which this base class will mainly move the projectile for all child projectiles
	// Returns			: Nothing
	//-------------------------------------------------------------------------------------------------------------------
	virtual void update( float deltaTime ) override;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: render(sf::RenderTarget* targetWindow)
	// Parameters		: targetWindow - the window to render object to
	// Purpose			: To render projectiles on to the screen
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void render( sf::RenderTarget* targetWindow ) override;

#pragma endregion

#pragma region getters and setters
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setProjectileType(const ProjectileTypes& projectileType)
	// Parameters		: projectileType - the type of the projectile will be
	// Purpose			: This will set the projectile type so it can be recognised and not mistaken by another projectile
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setProjectileType(const ProjectileTypes& projectileType);

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getProjectileType()
	// Parameters		: None
	// Purpose			: This will get the projectile type so it can be recognised and allow it to instantiate, or check  
	//					,	for specific collision detection with that projectile
	// Returns			: Get the projectile type that the game wants to recognise
	//---------------------------------------------------------------------------------------------------------------------
	const ProjectileTypes& getProjectileType() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setIsProjectileAlive(bool isProjectileAlive)
	// Parameters		: isProjectileAlive - Whether or not the projectile is alive
	// Purpose			: To set the alive state of the projectile, which will allow them to function
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setIsProjectileAlive(bool isProjectileAlive);

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getIsProjectileAlive()
	// Parameters		: None
	// Purpose			: This will get to check if the projectile is alive or not
	// Returns			: A boolean whether the projectile is alive or not
	//---------------------------------------------------------------------------------------------------------------------
	const bool getIsProjectileAlive() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setDamage(float damage)
	// Parameters		: damage - The desired amount of damage the projectile will deal
	// Purpose			: To set the damage that the projectile will deal to when overlapping
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setDamage( float damage );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getDamage()
	// Parameters		: None
	// Purpose			: This will get the damage amount the projectile deals to be used in collision detection
	// Returns			: Amount of damage that will be dealt
	//---------------------------------------------------------------------------------------------------------------------
	const float getDamage() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setProjectileSpeed(float projectileSpeed)
	// Parameters		: projectileSpeed - The desired speed the projectile will travel by
	// Purpose			: To set the speed, which will be constant for projectiles
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setProjectileSpeed(float projectileSpeed);

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setProjectileDirection(float projectileDirectionX , float projectileDirectionY)
	// Parameters		: projectileDirectionX - The desired direction on the X for the projectile
	//					, projectileDirectionY - The desired direction on the Y for the projectile
	// Purpose			: To set the direction, which will be used to move projectiles
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setProjectileDirection(float projectileDirectionX, float projectileDirectionY);

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getCircleCollider()
	// Parameters		: None
	// Purpose			: This will get the collision collider of the projectile, for collision detection
	// Returns			: The circle collider of the projectile
	//---------------------------------------------------------------------------------------------------------------------
	CircleCollider& getCircleCollider();

#pragma endregion
};

#endif // !PROJECTILEBASE_H
