#include "Settings.h"
#include "SpriteObject.h"

SpriteObject::SpriteObject()
//Set these booleans to false before the constructor is called
	: m_hasAnimationFinished			( false )
	, m_hasSpriteAnimationInitialised	( false )
	, m_isItSpriteSheet					( false )
	, m_isLooping						( false )
	, m_animationTime					( 0.0f )
	, m_frameCounter					( 1 )
{
}

SpriteObject::~SpriteObject()
{
}

void SpriteObject::loadSpriteTexture(const sf::Texture& texture, bool isItSpriteSheet)
{
	// Set the boolean if it is a sprite sheet or not
	m_isItSpriteSheet = isItSpriteSheet;

	//Set the texture 
	setTexture(texture);

	//Get the texture dimesions using unassigned int vector2
	m_textureDimensions = texture.getSize();

	//Check if the texture that got loaded, is not a sprite sheet
	if (m_isItSpriteSheet == false)
	{
		//Set the origin position of the loaded texture
		//Set the origin position by changing the dimensions to a float and half it to place the origin in the middle of the texture
		setOrigin( static_cast< float >( m_textureDimensions.x ) / 2.0f , static_cast< float >( m_textureDimensions.y ) / 2.0f );
	}
}

void SpriteObject::animateSpriteSheet( const sf::IntRect& spriteFrame , bool isLooping , float deltaTime, float maxFramesPerSecond , int maxAmountOfFrames )
{
	// Increment animation time by delta time
	m_animationTime += deltaTime;

	// Check if the sprite sheet has not yet been initialised
	// As this function will be in an update function. It is important to have this check, so that it doesn't initialise again
	if ( m_hasSpriteAnimationInitialised == false )
	{
		// Set the rectangle shape based on the frame size and it to the texture rectangle, to get the correct frame size
		m_rectangleSpriteFrame = spriteFrame;
		setTextureRect( m_rectangleSpriteFrame );

		// Set the origin in the middle of the first frame which would be used for every frame of the animation
		setOrigin( Settings::TextureProperties::c_spriteOriginPositionXY , Settings::TextureProperties::c_spriteOriginPositionXY );

		// Set if the animation is a looping one and set animation finished to false for animations that are not looping
		m_isLooping = isLooping;
		m_hasAnimationFinished = false;

		// Once all everything is set, the animation is initialised
		m_hasSpriteAnimationInitialised = true;
	}

	// Checking if the animation is above frame rate
	if( m_animationTime  > maxFramesPerSecond )
	{
		// Check if the frame counter is below max amount of frames in the animation
		if( m_frameCounter < maxAmountOfFrames )
		{
			m_rectangleSpriteFrame.left += Settings::TextureProperties::c_spriteFrameSizeXY; // Increment the texture coordinate on the x by the size of the sprite fram, which 32
			m_frameCounter++; // Increment the frameCounter
		}
		else // If the frame counter has reached above the max frame amount
		{
			// Set the texture coordinate x back to the beginning, which is the first frame and set the frame counter to 1
			m_rectangleSpriteFrame.left = 0;
			m_frameCounter = 1;

			// Check if the animation is not a looping animation
			if ( m_isLooping == false )
			{
				// Tell the classes, that have non-looping animations that it has finished
				m_hasAnimationFinished = true;
			}
		}

		// Set texture rectangle on the current frame and set animation time back to 0
		setTextureRect( m_rectangleSpriteFrame );
		m_animationTime = 0;
	}
}

void SpriteObject::setHasSpriteAnimationInitialised( bool hasSpriteAnimationInitialised )	{ m_hasSpriteAnimationInitialised = hasSpriteAnimationInitialised; }

const bool SpriteObject::getHasAnimationFinished() const									{ return m_hasAnimationFinished; }
