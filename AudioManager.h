#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <map>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/String.hpp>

// The sounds that will used in the game
enum class GameSounds
{
	EnemyProjectile, Music , PlayerProjectile,  Score
};

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: AudioManager
// Classes Inherited	: None
// Purpose				: To manage and store all of the sounds in this class, so it can be accessed by anything that 
//						,	requires sound output
//-------------------------------------------------------------------------------------------------------------------------
class AudioManager
{
private:
#pragma region private variables
	sf::Sound								m_soundEffect; // This will play the sound effects
	sf::Sound								m_music; // This will play the music

	// This map stores all sounds that is recognised using the "GameSounds" enum as their ID
	std::map<GameSounds , sf::SoundBuffer*> m_soundTable; // 
#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: AudioManager()
	// Parameters		: None
	// Notes			: This constructor will initialise nothing but itself
	//---------------------------------------------------------------------------------------------------------------------
	AudioManager();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: AudioManager()
	// Parameters		: None
	// Notes			: This destructor will delete every audio in the map
	//---------------------------------------------------------------------------------------------------------------------
	~AudioManager();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: loadAudio(GameSounds audioID , const sf::String& audioFileAddress)
	// Parameters		: audioID - This is the audio ID that will add the sound to represent the ID
	//					, audioFileAddress - This is the file path to the audio file
	// Purpose			: This will load the sound file and set it to the container
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void loadAudio( GameSounds audioID , const sf::String& audioFileAddress );

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: playAudio(GameSounds audioID)
	// Parameters		: audioID - This is the audio ID will be to retrieve the correct audio file to play it
	// Purpose			: This will get the sond file from the container and play the sound
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void playAudio( GameSounds audioID );

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: stopAudio
	// Parameters		: None
	// Purpose			: This will the sound effect from playing
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void stopAudio();
};

#endif // !AUDIOMANAGER_H
