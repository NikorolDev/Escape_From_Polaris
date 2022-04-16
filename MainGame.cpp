#include <SFML/Window/Event.hpp>

#include "AudioManager.h"
#include "CollisionManager.h"
#include "EnemyManager.h"
#include "Helpers.h"
#include "HighScoreScreen.h"
#include "HUD.h"
#include "MainGame.h"
#include "ParticleManager.h"
#include "Player.h"
#include "ProjectileManager.h"
#include "Settings.h"
#include "TextureManager.h"

MainGame::MainGame()
// Setting these variables before the constructor gets called
	: m_pAudioManager	( nullptr )
	, m_pHighScoreScreen( nullptr )
	, m_pWindow			( nullptr )
{
	// Create new objects
	m_pCollisionManager		= new CollisionManager();
	m_pEnemyManager			= new EnemyManager();
	m_pHUD					= new HUD();
	m_pParticleManager		= new ParticleManager();
	m_pPlayer				= new Player();
	m_pProjectileManager	= new ProjectileManager();
}

MainGame::~MainGame()
{
	// Safe delete all of the pointers that were created using new
	safeDeletePointer( m_pProjectileManager );
	safeDeletePointer( m_pPlayer );
	safeDeletePointer( m_pParticleManager );
	safeDeletePointer( m_pHUD );
	safeDeletePointer( m_pEnemyManager );
	safeDeletePointer( m_pCollisionManager );
}

void MainGame::initialise( AudioManager* pAudioManager , TextureManager* pTextureManager , HighScoreScreen* pHighScoreScreen )
{
	m_pAudioManager		= pAudioManager;
	m_pHighScoreScreen	= pHighScoreScreen;

	// Initialise classes that require pointers that been created in this constructor. This will avoid the creation of the same class
	m_pCollisionManager->	initialise( pAudioManager , m_pEnemyManager , m_pPlayer , m_pProjectileManager );
	m_pEnemyManager->		initialise( pAudioManager , pTextureManager , m_pPlayer , m_pProjectileManager );
	m_pParticleManager->	initialise( pTextureManager );
	m_pPlayer->				initialise( pAudioManager , m_pProjectileManager , pTextureManager );
	m_pHUD->				initialise( m_pPlayer , pTextureManager );
}

void MainGame::run( sf::RenderWindow* window )
{
	// Create the game window using the set window width and height
	m_pWindow = window;

	// Set a new game
	setNewGame();

	// Create a deltaTime float varaible so that we can update any movements frame rate independently
	float deltaTime = 0;

	// While the window is still open
	while ( m_pPlayer->getIsPlayerAlive() == true )
	{
		// Restart the clock every loop so that new time has passed
		m_gameClock.restart();

		// Check for any window events
		handleWindowEvent();

		// Clear the screen
		m_pWindow->clear();

		// Update necessary objects using deltaTime
		update(deltaTime);

		// Render necessary objects
		render();

		// Display it on the window
		m_pWindow->display();
		
		// Set the delta time that was passed since the gameClock restarted
		deltaTime = m_gameClock.getElapsedTime().asSeconds();
	}

	// Check if the window is still open
	if ( m_pWindow->isOpen() )
	{
		// Stop sound effects
		m_pAudioManager->stopAudio();

		// Pass the player's score to the high score screen
		m_pHighScoreScreen->setFinalScore( m_pPlayer->getScore() );

		// Run the high score screen, passing the window and from which state it was opened.
		// This will display either to enter scores or that the player needs to get certain amount of points get into the highscore board
		m_pHighScoreScreen->run( m_pWindow , OpenedFromStates::MainGame );
	}
}

void MainGame::handleWindowEvent()
{
	//This event variable will be used to check for windw events
	sf::Event event;

	// This while loop will check if any events have been triggered.
	// If no window events have been triggered, keep the game running
	while (m_pWindow->pollEvent(event))
	{
		// Check if the event was to close the game
		if (event.type == sf::Event::Closed)
		{
			// Close the window
			m_pWindow->close();
 			m_pPlayer->setIsPlayerAlive( false );
		}
	}
}

void MainGame::update(float deltaTime)
{
	// Update these classes that uses delta time, for frame independant updating
	m_pEnemyManager->		update( deltaTime );
	m_pPlayer->				update( deltaTime );
	m_pProjectileManager->	update( deltaTime );
	m_pParticleManager->	update( deltaTime );

	// Update the classes, which does not uses delta time because there's nothing to update that needs to be frame rate independent
	m_pCollisionManager->	update();
	m_pHUD->				update();
}

void MainGame::render()
{
	// Render all of these classes
	m_pParticleManager->	render( m_pWindow );
	m_pProjectileManager->	render( m_pWindow );
	m_pEnemyManager->		render( m_pWindow );
	m_pPlayer->				render( m_pWindow );
	m_pHUD->				render( m_pWindow );
}

void MainGame::setNewGame()
{
	// Reset enemies, clear projectiles and set the player
	m_pEnemyManager->resetEnemies();
	m_pProjectileManager->clearProjectiles();
	m_pPlayer->setPlayer();
}
