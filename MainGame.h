#ifndef MAINGAME_H
#define MAINGAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

// Forward class declarations
class AudioManager;
class CollisionManager;
class EnemyManager;
class HighScoreScreen;
class HUD;
class ParticleManager;
class Player;
class ProjectileManager;
class TextureManager;

//-------------------------------------------------------------------------------------------------------------------------
// Class Name			: MainGame
// Classes Inherited	: None
// Purpose				: To handle how the game will run based on updating and drawing objects
//-------------------------------------------------------------------------------------------------------------------------
class MainGame
{
private:
#pragma region private variables
	AudioManager*		m_pAudioManager; // To stop all audio when player dies
	CollisionManager*	m_pCollisionManager; // Collision manager that will call its updater for checking collisions
	EnemyManager*		m_pEnemyManager; // Enemy Manager that will update and render all enemies
	HighScoreScreen*	m_pHighScoreScreen; // The high score screen to run after the player dies
	HUD*				m_pHUD; // Heads Up Display (HUD) which will that will update and render soem graphical informaition
	ParticleManager*	m_pParticleManager; // Particle manager will update all particles and display them
	Player*				m_pPlayer; // Player that will mover, shoot and render
	ProjectileManager*	m_pProjectileManager; // Projectile manager that will update and render each projectile

	sf::Clock			m_gameClock; // This clock will be used to get elapsed time so that the game update some classes frame rate indepently
	sf::RenderWindow*	m_pWindow; // The game window that will display our game

#pragma endregion

#pragma region private functions
	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: handleWindowEvent()
	// Parameters		: None
	// Purpose			: To handle window events, for example when window closes
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void handleWindowEvent();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: update(float deltaTime)
	// Parameters		: deltaTime - This will be used to make our movements smoother and frame rate independent
	// Purpose			: This will update all necessary objects as the game is running
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void update(float deltaTime);

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: render()
	// Parameters		: None
	// Purpose			: This will render all necessary objects as the game is running
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void render();

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: setNewGame()
	// Parameters		: None
	// Purpose			: This will set a new game for the user, by resetting necesseary for player, enemies and 
	//					,	projectiles
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void setNewGame();

#pragma endregion

public:
#pragma region constructors and destructors
	//---------------------------------------------------------------------------------------------------------------------
	// Constructor name	: MainGame()
	// Parameters		: None
	// Notes			: This will initialise private variables and initialise pointers
	//---------------------------------------------------------------------------------------------------------------------
	MainGame();

	//---------------------------------------------------------------------------------------------------------------------
	// Destructor name	: MainGame()
	// Parameters		: None
	// Notes			: This destructor will delete all the pointers made
	//---------------------------------------------------------------------------------------------------------------------
	~MainGame();

#pragma endregion

#pragma region public functions	
	//---------------------------------------------------------------------------------------------------------------------
	// Function Name	: initialise(AudioManager* pAudioManager , TextureManager* pTextureManager , HighScoreScreen* pHighScoreScreen)
	// Parameters		: pAudioManager = to play sounds to given objects
	//					, pTextureManager - to pass the texture managers to class tha need to set their textures
	//					, pHighScoreScreen - to be able to run the high score screen from the main menu
	// Purpose			: This initialise function will pass the texture manger to objects that need to set their textures 
	//					,	and set the high score screnn to be able to run it
	// Returns			: Nothing
	//---------------------------------------------------------------------------------------------------------------------
	void initialise( AudioManager* pAudioManager , TextureManager* pTextureManager , HighScoreScreen* pHighScoreScreen );

	//---------------------------------------------------------------------------------------------------------------------
	// Function name	: run()
	// Parameters		: window - The window that will display the scores
	// Purpose			: This function will keep the game running by checking if the player is still alive. It will also 
	//					,	update, render objects and display it on the game window
	// Returns			: Nothing
	//--------------------------------------------------------------------------------------------------------------------
	void run( sf::RenderWindow* window );

#pragma endregion
};

#endif // !MAINGAME_H
