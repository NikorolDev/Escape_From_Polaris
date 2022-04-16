#ifndef STARPARTICLE_H
#define STARPARTICLE_H

#include <SFML/Graphics/CircleShape.hpp>
#include "SpriteObject.h"

// Forward class declaration of texture manager
class TextureManager;

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: StarParticle
// Classes Inherited	: SpriteObject
// Purpose				: To handle basic particle movement and rendering
//------------------------------------------------------------------------------------------------------------------------
class StarParticle : public SpriteObject
{
private:
#pragma region private variables
	bool			m_isAlive; // This is to check if the particle is alive

	float			m_speed; // The speed of the particle

	sf::Vector2f	m_direction; // The direction the particle will head towards

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: StarParticle()
	// Parameters		: None
	// Notes			: As this is a default constructor it will initialise private variables
	//---------------------------------------------------------------------------------------------------------------------
	StarParticle();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: StarParticle()
	// Parameters		: None
	// Notes			: This destructor will delete itself
	//---------------------------------------------------------------------------------------------------------------------
	~StarParticle();

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: initialise(TextureManager* pTextureManager)
	// Parameters		: pTextureManager - A passed through pointer of the texture manager to set the texture for star 
	//					,	particles
	// Purpose			: To use the passed through texture manager to set the texture of the star particles
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void initialise( TextureManager* pTextureManager );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: update(float deltaTime)
	// Parameters		: deltaTime - This will be used to update the movement of particles
	// Purpose			: This overridden update function will update the movement of particles
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void update( float deltaTime ) override;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: render(sf::RenderTarget* targetWindow)
	// Parameters		: targetWindow - the window to render object to
	// Purpose			: To render the particle's onto the screen
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	virtual void render( sf::RenderTarget* targetWindow ) override;

#pragma endregion

#pragma region getters and setters
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setIsAlive(bool isAlive)
	// Parameters		: isAlive - setting the active state of the particles
	// Purpose			: To set the active state of the particles
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setIsAlive( bool isAlive );

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: getIsAlive()
	// Parameters		: None
	// Purpose			: To get the active state of the particles
	// Returns			: Wheter or not a particle is active or not
	//---------------------------------------------------------------------------------------------------------------------
	const bool getIsAlive() const;

	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setDirection(sf::Vector2f direction)
	// Parameters		: direction - setting the desired direction
	// Purpose			: To set the direction of the particles
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setDirection( sf::Vector2f direction );

#pragma endregion
};


#endif // !STARPARTICLE_H
