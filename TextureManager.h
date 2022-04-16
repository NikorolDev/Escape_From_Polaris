#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>

// Enum of all textures in the game
enum class GameTextures
{
	BiterEnemyTexture , DasherEnemyTexture , FighterEnemyTexture ,  HealthBarTexture , HelpScreen , PlayerTexture , PowerUpBarTexture , ProjectileEnemyTexture , ProjectilePlayerTexture , ProjectileRapidPlayerTexture  , StarTexture
};

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: TextureManager
// Classes Inherited	: None
// Purpose				: To manage and store all of the textures in this class, so it can be accessed by any sprite object 
//-------------------------------------------------------------------------------------------------------------------------
class TextureManager
{
private:
#pragma region private variables
	// This map stores all textures that is recognised using the "GameTextures" enum as their ID
	std::map<GameTextures, sf::Texture*> m_textureTable;

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: TextureManager()
	// Parameters		: None
	// Notes			: This constructor will initialise nothing but itself
	//---------------------------------------------------------------------------------------------------------------------
	TextureManager();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: TextureManager()
	// Parameters		: None
	// Notes			: This destructor will delete every texture in the map
	//---------------------------------------------------------------------------------------------------------------------
	~TextureManager();

#pragma endregion

#pragma region public functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: loadTexture(GameTextures textureID , const sf::String& textureFileAddress)
	// Parameters		: textureID - This is the texture ID that will add the texture to represent the ID
	//					, textureFileAddress - This is the file path to the texture
	// Purpose			: This will load the texture and set it to the container
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void loadTexture( GameTextures textureID , const sf::String& textureFileAddress );

#pragma endregion

#pragma region getters and setters
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: getTexture( GameTextures textureID )
	// Parameters		: textureID - This will be used to retrieve the correct texture based on the ID
	// Purpose			: To retrieve the texture based on the ID that has been passed through
	// Returns			: The desired texture
	//---------------------------------------------------------------------------------------------------------------------
	const sf::Texture& getTexture( GameTextures textureID );

#pragma endregion

};

#endif // !TEXTUREMANAGER_H
