#include "Helpers.h"
#include "ParticleManager.h"
#include "Settings.h"

ParticleManager::ParticleManager()
{
	// Create new particles to be used in the game
	m_pStarParticles = new StarParticle[ Settings::ParticleProperties::c_maxAmountOfStarParticles ];
}

ParticleManager::~ParticleManager()
{
	// Delete the array of particles
	safeDeletePointerArray( m_pStarParticles );
}

void ParticleManager::initialise( TextureManager* pTextureManager )
{
	// Loop through all particles in the array and initialise them, by passing through the texture manager
	for ( int starParticleID = 0; starParticleID < Settings::ParticleProperties::c_maxAmountOfStarParticles; ++starParticleID )
	{
		m_pStarParticles[ starParticleID ].initialise( pTextureManager );
	}
}

void ParticleManager::update( float deltaTime )
{
	// Loop through all particles
	for ( int starParticleID = 0; starParticleID < Settings::ParticleProperties::c_maxAmountOfStarParticles; ++starParticleID )
	{
		// Check if the particle is not alive
		if ( m_pStarParticles[ starParticleID ].getIsAlive() == false )
		{
			// Generate particle properties and set it to be alive
			setParticleProperties( starParticleID );
			m_pStarParticles[ starParticleID ].setIsAlive( true );
		}
		else
		{
			// Update the particles
			m_pStarParticles[ starParticleID ].update( deltaTime );
		}
	}
}

void ParticleManager::render( sf::RenderTarget* targetWindow )
{
	// Loop through all particles
	for ( int starParticleID = 0; starParticleID < Settings::ParticleProperties::c_maxAmountOfStarParticles; ++starParticleID )
	{
		// If the particle is alive
		if ( m_pStarParticles[ starParticleID ].getIsAlive() == true )
		{
			// Render the particle
			m_pStarParticles[ starParticleID ].render( targetWindow );
		}
	}
}

void ParticleManager::setParticleProperties( const int particleID )
{
	// Set the direction and position for the projectiles. 
	//This will set randomised direction on the y, which manipulates the speed and set random position along the X axis
	m_pStarParticles[ particleID ].setDirection		( sf::Vector2f( 0 , generateRandomFloat( 0 , 1 ) ) );
	m_pStarParticles[ particleID ].setPosition		( generateRandomFloat( 0 , 800 ) , 0 );
}
