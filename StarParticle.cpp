#include "TextureManager.h"
#include "Settings.h"
#include "StarParticle.h"

StarParticle::StarParticle()
// Setting these variables before the constructor gets called
	: m_isAlive	( false )
	, m_speed	( Settings::ParticleProperties::c_particleSpeed )
{
}

StarParticle::~StarParticle()
{
}

void StarParticle::initialise( TextureManager* pTextureManager )
{
	// Load the texture for the particles
	loadSpriteTexture( pTextureManager->getTexture( GameTextures::StarTexture ) , false );
}

void StarParticle::update( float deltaTime )
{
	// Move the particle in given direction with the addition of speed and deltaTime
	move( ( m_direction * m_speed ) * deltaTime );

	// Check the position of the particle, if it's below the screen
	if ( getPosition().y > Settings::Positions::c_lowestPointToDespawn )
	{
		// Deactivate the particle, which will reset it
		m_isAlive = false;
	}
}

void StarParticle::render( sf::RenderTarget* targetWindow )
{
	// Render the particle
	targetWindow->draw( *this );
}

void StarParticle::setIsAlive( bool isAlive )				{ m_isAlive = isAlive; }

const bool StarParticle::getIsAlive() const					{ return m_isAlive; }

void StarParticle::setDirection( sf::Vector2f direction )	{ m_direction = direction; }
