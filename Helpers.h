#ifndef HELPERS_H
#define HELPERS_H

#include <cassert>
#include <SFML/System/Vector2.hpp>

//---------------------------------------------------------------------------------------------------------------------
// Function name	: safeDeletePointer(T* &pointer)
// Parameters		: pointer - A single pointer that needs to be deleted
// Purpose			: This will delete a pointer and set it to nullptr
// Returns			: Nothing
//---------------------------------------------------------------------------------------------------------------------
template <typename T> void safeDeletePointer( T* &pointer )
{
	delete pointer;
	pointer = nullptr;
}

//---------------------------------------------------------------------------------------------------------------------
// Function name	: safeDeletePointer(T* &pointerArray)
// Parameters		: pointerArray - A pointer array that needs to be deleted
// Purpose			: This will delete a pointer array and set it to nullptr
// Returns			: Nothing
//---------------------------------------------------------------------------------------------------------------------
template <typename T> void safeDeletePointerArray( T* &pointerArray )
{
	delete[] pointerArray;
	pointerArray = nullptr;
}

//---------------------------------------------------------------------------------------------------------------------
// Function name	: generateRandomFloat(float minValue , float maxValue)
// Parameters		: minValue - minimum value to randomise
//					, maxValue - maximum value to randomise
// Purpose			: This will return a randomised float value
// Returns			: a randomised float value
//---------------------------------------------------------------------------------------------------------------------
float generateRandomFloat( float a , float b );

//---------------------------------------------------------------------------------------------------------------------
// Function name	: floatLerp( const float startingFloatValue , const float endingFloatValue , float time)
// Parameters		: startingFloatValue - Starting float value to lerp from
//					, endingFloatValue - Ending float value to lerp to
//					, time - current time to get to that value
// Purpose			: This will return an interpolated float value to get from point A to B
// Returns			: An interpolated float value
//---------------------------------------------------------------------------------------------------------------------
float floatLerp( const float startingFloatValue , const float endingFloatValue , float time );

//---------------------------------------------------------------------------------------------------------------------
// Function name	: vectorLerp(const sf::Vector2f& startingPosition , const sf::Vector2f& endPosition , float time)
// Parameters		: startingPosition - Starting position to lerp from
//					, endPosition - Ending position to lerp to
//					, time - current time to get to that value
// Purpose			: This will return an interpolated vector position to get from point A to B
// Returns			: An interpolated vector position
//---------------------------------------------------------------------------------------------------------------------
sf::Vector2f vectorLerp( const sf::Vector2f& startingPosition , const sf::Vector2f& endPosition , float time );

#ifdef _DEBUG
	#define ASSERT assert
#else
	#define ASSERT
#endif

#endif // !HELPERS_H
