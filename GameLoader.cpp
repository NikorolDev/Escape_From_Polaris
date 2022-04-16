#include "AudioManager.h"
#include "GameLoader.h"
#include "Helpers.h"
#include "HighScoreScreen.h"
#include "MainGame.h"
#include "MainMenu.h"
#include "Settings.h"
#include "TextureManager.h"

GameLoader::GameLoader()
{
	// Create new states and a texturemanager
	m_pAudioManager		= new AudioManager();
	m_pHighScoreScreen	= new HighScoreScreen();
	m_pMainGame			= new MainGame();
	m_pMainMenu			= new MainMenu();
	m_pTextureManager	= new TextureManager();
}

GameLoader::~GameLoader()
{
	// Delete these pointers as they were created as new
	safeDeletePointer( m_pTextureManager );
	safeDeletePointer( m_pMainMenu );
	safeDeletePointer( m_pMainGame );
	safeDeletePointer( m_pHighScoreScreen );
	safeDeletePointer( m_pAudioManager );
}

void GameLoader::initialise()
{
	// load all audio files and textures into the game
	loadAudio();
	loadTextures();

	// Initialise states
	m_pHighScoreScreen->initialise();
	m_pMainGame->initialise( m_pAudioManager , m_pTextureManager , m_pHighScoreScreen );
	m_pMainMenu->initialise( m_pAudioManager , m_pTextureManager , m_pMainGame , m_pHighScoreScreen );

	// Create the game window using the set window width and height
	m_window.create( sf::VideoMode( Settings::Window::c_windowWidth , Settings::Window::c_windowHeight ) , "Escape From Polaris" );

	// Run main menu first, by passing through the window and texture manager
	m_pMainMenu->run( &m_window );
}

void GameLoader::loadAudio()
{
	// Load all sounds into the game
	m_pAudioManager->loadAudio( GameSounds::EnemyProjectile ,	Settings::AudioFiles::c_enemyProjectileAudioAddress );
	m_pAudioManager->loadAudio( GameSounds::Music ,				Settings::AudioFiles::c_musicAudioAddress );
	m_pAudioManager->loadAudio( GameSounds::PlayerProjectile ,	Settings::AudioFiles::c_playerProjectileAudioAddress );
	m_pAudioManager->loadAudio( GameSounds::Score ,				Settings::AudioFiles::c_scoreAudioAddress );
}

void GameLoader::loadTextures()
{
	// Load all textures into the game 
	m_pTextureManager->loadTexture( GameTextures::BiterEnemyTexture ,				Settings::TextureFiles::c_biterEnemyTextureAddress );
	m_pTextureManager->loadTexture( GameTextures::DasherEnemyTexture ,				Settings::TextureFiles::c_dasherEnemyTextureAddress );
	m_pTextureManager->loadTexture( GameTextures::FighterEnemyTexture ,				Settings::TextureFiles::c_fighterEnemyTextureAddress );
	m_pTextureManager->loadTexture( GameTextures::HealthBarTexture ,				Settings::TextureFiles::c_playerHealthBarTextureAddress );
	m_pTextureManager->loadTexture( GameTextures::HelpScreen ,						Settings::TextureFiles::c_helpScreenTextureAddress );
	m_pTextureManager->loadTexture( GameTextures::PlayerTexture ,					Settings::TextureFiles::c_playerTextureAddress );
	m_pTextureManager->loadTexture( GameTextures::PowerUpBarTexture ,				Settings::TextureFiles::c_playerPowerUpBarTextureAddress );
	m_pTextureManager->loadTexture( GameTextures::ProjectileEnemyTexture ,			Settings::TextureFiles::c_projectileEnemyTextureAddress );
	m_pTextureManager->loadTexture( GameTextures::ProjectilePlayerTexture ,			Settings::TextureFiles::c_projectilePlayerTextureAddress );
	m_pTextureManager->loadTexture( GameTextures::ProjectileRapidPlayerTexture ,	Settings::TextureFiles::c_projectileRapidPlayerTextureAddress );
	m_pTextureManager->loadTexture( GameTextures::StarTexture ,						Settings::TextureFiles::c_starTextureAddress );
}