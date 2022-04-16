#include "Helpers.h"
#include "TextureManager.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{	
	//Loop through the texture table
	for (auto texturePointer : m_textureTable)
	{
		//Delete a texture pointer, which is the second column of the map
		delete texturePointer.second;
		texturePointer.second = nullptr;
	}
}

void TextureManager::loadTexture( GameTextures textureID , const sf::String& textureFileAddress )
{
	// Based on the texture ID, create a new texture and load it to the map, so that it can be accessed to set it for each sprite
	m_textureTable[ textureID ] = new sf::Texture();
	bool successfullyLoaded = m_textureTable[ textureID ]->loadFromFile( textureFileAddress );

	// Check if the texture has not loaded successfully, it will call the assert to show that a texture has not loaded successfully
	ASSERT( successfullyLoaded );
}

const sf::Texture& TextureManager::getTexture(GameTextures textureID)
{
	// Find the texture based on the ID that was passed through and return the texture
	auto foundTexture = m_textureTable.find(textureID);
	return *foundTexture->second;
}
