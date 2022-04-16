#ifndef PARTICLEMANAGER
#define PARTICLEMANAGER

#include "Object.h"
#include "StarParticle.h"

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: ParticleManager
// Classes Inherited	: Object
// Purpose				: To handle every particle that will be in the game
//------------------------------------------------------------------------------------------------------------------------
class ParticleManager : public Object
{
private:
#pragma region private variables
	StarParticle* m_pStarParticles; // Pointer of start particles, which would be a pointer array

#pragma endregion

#pragma region private functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: setParticleProperties(int particleID)
	// Parameters		: particleID - The index of the particle in the array to generate
	// Purpose			: To set the particle properties
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setParticleProperties( const int particleID );

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: ParticleManager()
	// Parameters		: None
	// Notes			: This contructor will create new particle array
	//---------------------------------------------------------------------------------------------------------------------
	ParticleManager();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: ParticleManager()
	// Parameters		: None
	// Notes			: This destructor will delete the particle pointer array
	//---------------------------------------------------------------------------------------------------------------------
	~ParticleManager();

#pragma endregion

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

};

#endif // !PARTICLEMANAGER
