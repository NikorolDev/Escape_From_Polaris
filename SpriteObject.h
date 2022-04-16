#ifndef SPRITEOBJECT_H
#define SPRITEOBJECT_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>

#include "Object.h"

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: SpriteObject
// Classes Inherited	: Object and sf::Sprite
// Purpose				: To handle every sprite object that will be a sprite
//-------------------------------------------------------------------------------------------------------------------------
class SpriteObject : public Object, public sf::Sprite
{
private:
#pragma region private variables
	bool			m_hasAnimationFinished; // This will be used to check if the animation has finished
	bool			m_hasSpriteAnimationInitialised; // This will be used to check if the sprite sheet has been initialised
	bool			m_isItSpriteSheet; // This will be used to check if the texture that got loaded is a spriteSheet
	bool			m_isLooping; // This is to set the naimation as a non looping, which will animate only once

	float			m_animationTime; // The time that was passed in the animation

	int				m_frameCounter; // The frame counter will be used to check if it has met max amount of frames in an animation

	sf::IntRect		m_rectangleSpriteFrame; // To split the sprite sheet into seperate frames
	sf::Vector2u	m_textureDimensions; // The dimensions of the texture so it will be easier to set the spritesheet frame and origin of the texture

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: SpriteObject()
	// Parameters		: None
	// Notes			: This constructor will initialise nothing as the texture variable has its own constructor
	//---------------------------------------------------------------------------------------------------------------------
	SpriteObject();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: SpriteObject()
	// Parameters		: None
	// Notes			: This destructor will delete itself as no pointers will be initialised
	//---------------------------------------------------------------------------------------------------------------------
	~SpriteObject();

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: loadSpriteTexture(const sf::Texture& texture, bool isItSpriteSheet)
	// Parameters		: texture - This is the texture that will be used for the desired sprite object
	//					, isItSpriteSheet - This will be used to check if the texture is a sprite sheet or not
	// Purpose			: This will load the texture for the child of SpriteObject (this class)
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void loadSpriteTexture(const sf::Texture& texture, bool isItSpriteSheet);

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: animateSpriteSheet(const sf::IntRect& spriteFrame , bool isLooping , float deltaTime , float maxFramesPerSecond , int maxAmountOfFrames)
	// Parameters		: spriteFrame - the coordinates of the frame that will be used in the animation
	//					, isLooping - if the animation is looping
	//					, deltaTime - time to be used for switching to next frame based on frames per second
	//					, maxFramesPerSecond - max frame rate on the animation
	//					, maxAmountOfFrames - max amount of frames in the animation
	// Purpose			: This will animate the animation state from the spriteObject using the texture coordinates using the IntRect
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void animateSpriteSheet( const sf::IntRect& spriteFrame , bool isLooping , float deltaTime , float maxFramesPerSecond , int maxAmountOfFrames );

#pragma endregion

#pragma region getters and setters
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: setHasSpriteAnimationInitialised(bool hasSpriteAnimationInitialised)
	// Parameters		: hasSpriteAnimationInitialised - if the animation should be initialised/reinitialised
	// Purpose			: This will set if the animation should be initialised for setting the animation
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setHasSpriteAnimationInitialised( bool hasSpriteAnimationInitialised );

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: getHasAnimationFinished()
	// Parameters		: None
	// Purpose			: This will get if the animation has finished
	// Returns			: A boolean for if the animation has finished its animation
	//---------------------------------------------------------------------------------------------------------------------
	const bool getHasAnimationFinished() const;

#pragma endregion

};

#endif // !SPRITEOBJECT_H
