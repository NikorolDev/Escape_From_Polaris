//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// References:
// Wim. ( 2011 ). Generate random float between two floats [online]. Available: https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats/5289624 [Last accessed 14th January 2021].
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <cstdlib>

#include "Helpers.h"

float generateRandomFloat( float minValue , float maxValue )
{
	float randomlyGeneratedFloat = ( ( float ) rand() ) / ( float ) RAND_MAX;	// Randomise a float and divide it by max value that can be randomised
	float difference = maxValue - minValue;										// Calculate the distance between max and min float values
	float randomNumber = randomlyGeneratedFloat * difference;					// Multiply the randomly generated float with difference to get a random float within the range
	return minValue + randomNumber;												// Add Minimum value  to random number to get it in range 
}

float floatLerp( const float startingFloatValue , const float endingFloatValue , float time )
{
	return startingFloatValue + time * ( endingFloatValue - startingFloatValue );
}

sf::Vector2f vectorLerp(const sf::Vector2f& startingPosition, const sf::Vector2f& endPosition, float time)
{
	return startingPosition + time * ( endPosition - startingPosition );
}
