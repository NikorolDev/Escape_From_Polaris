#include "AudioManager.h"
#include "Helpers.h"
#include "Settings.h"

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
	// Go through all sounds in the map
	for ( auto audioPointer : m_soundTable )
	{
		// Delete the second of the ma row and set it as nullptr
		delete audioPointer.second;
		audioPointer.second = nullptr;
	}
}

void AudioManager::loadAudio( GameSounds audioID , const sf::String& audioFileAddress )
{
	// Using the audioID create a new sound buffer and check if it can be loaded into the game, which will then store it on the map if true
	m_soundTable[ audioID ] = new sf::SoundBuffer();
	bool successfullyLoaded = m_soundTable[ audioID ]->loadFromFile( audioFileAddress );

	// Throw an assert, to stop the program when the audio file could not be loaded in
	ASSERT( successfullyLoaded );
}

void AudioManager::playAudio( GameSounds audioID )
{
	// Find the sound file based on the ID
	auto foundAudio = m_soundTable.find( audioID );

	// Switch based on the audioID to play the sound
	switch ( audioID )
	{
		// For every sound effect, it will set the buffer for the sound to be played 
		case GameSounds::EnemyProjectile:
		{
			m_soundEffect.setBuffer( *foundAudio->second );
			m_soundEffect.play();
			break;
		}

		case GameSounds::Music:
		{
			// For the music, set the buffer, set the volume and looping to true and play the sound
			m_music.setBuffer( *foundAudio->second );
			m_music.setVolume( 50.0f );
			m_music.setLoop( true );
			m_music.play();
		}

		case GameSounds::PlayerProjectile:
		{
			m_soundEffect.setBuffer( *foundAudio->second );
			m_soundEffect.play();
		}

		case GameSounds::Score:
		{
			m_soundEffect.setBuffer( *foundAudio->second );
			m_soundEffect.play();
		}
	}
}

void AudioManager::stopAudio()
{
	// Stop the sound effect to prevent it from playing in other ares
	m_soundEffect.stop();
}
