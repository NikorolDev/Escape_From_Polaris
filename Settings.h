#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

namespace Settings
{
	const float c_pi											= 3.142f; // A pi value used for settings angle

	namespace AudioFiles
	{
		// The file addresses of all sounds used in the game
		const sf::String c_enemyProjectileAudioAddress			= "Assets/Audio/ProjectileEnemy.wav";
		const sf::String c_musicAudioAddress					= "Assets/Audio/Cosmic-Phaera.wav";
		const sf::String c_playerProjectileAudioAddress			= "Assets/Audio/ProjectilePlayer.wav";
		const sf::String c_scoreAudioAddress					= "Assets/Audio/Score.wav";
	}

	namespace Colours
	{
		// The colours that will be used throughout the game
		const sf::Color c_green									= sf::Color( 0 , 255 , 0 , 255 );
		const sf::Color c_red									= sf::Color( 255 , 0 , 0 , 255 );
		const sf::Color c_white									= sf::Color( 255 , 255 , 255 , 255 );
	}

	namespace EnemyProperties
	{
		const float c_formationPositionY						= 80.0f; // enemy's formation position on the Y, which isused as an incrementor as well
		const float c_leftFromationOffsetX						= 500.0f; // The offset to the formation from left off screen position
		const float c_maxSpawningLeftPositionX					= 0.0f; // The max position on X of where enemies can spawn on the left
		const float c_maxSpawningRightPositionX					= 1100.0f; // The max position on X of where enemies can spawn on the right
		const float c_rightFromationOffsetX						= -400.0f; // The offset to the formation from right off screen position
		const float c_spawnLeftPoisitionX						= -400.0f; // The starting position on the left position X
		const float c_spawnRightPoisitionX						= 900.0f; // The starting position on the right position X
		const float c_spawningPositionXIncrementor				= 100.0f; // The spawning position incrementor on the X

		const int	c_formationHeight							= 4; // Formation height
		const int	c_formationWidth							= 7; // Formation width
		const int	c_maxAmountOfEachEnemyTypes					= 20; // The amount of each type of enemy
		const int	c_maxAmountOfEnemyTypes						= 4; // Max amount of enemy types
		const int	c_maxAmountOfEnemies						= 60; // Max amount of enemies that will be in the game

		namespace BiterProperties 
		{
			const float c_damage								= 20.0f; // The amount of damage the biter will deal to the player
			const float c_maxHealthPoints						= 20.0f; // The max amount of health points the biter is given when spawned
			const float c_maxSpeedX								= 0.1f;  // The max biter speed on the X axis
			const float c_maxSpeedY								= 70.0f; // The max biter speed on the Y axis
			const float c_centrelineOffset						= 50.0f; // The offset amount of the centreline in the biter's sine wave movement
			const float c_speedIncrementor						= 0.05f; // The amount of speed will be added per tick
			
			const int	c_maxAmountOfAnimationFrames			= 18; // The max amount of frames in the biter's animation
		}

		namespace DasherProperties
		{
			const float c_damage								= 50.0f; // The amount od damage the dasher will deal to the player
			const float c_directionY							= 0.5f; // The direction that will be towards the player, which is going down
			const float c_maxHealthPoints						= 50.0f; // The max amount of health points the dasher is given when spawned
			const float c_maxTimeToCharge						= 1.0f; // The max amount of charge needed for the dasher to attack the player
			const float c_speed									= 2000.0f; // The speed of the dasher

			const int	c_maxAmountOfAnimationFrames			= 17; // The max amount of frames in the dasher's animation
		}

		namespace FighterProperties
		{
			const float c_maxHealthPoints						= 50.0f; // The max amount of health points the dasher is given when spawned 
			const float c_shootingRate							= 1.0f; // The rate that fighter's will fire their projectiles

			const int	c_maxAmountOfAnimationFrames			= 17; // The max amount of frames in the fighter's animation
		}

		namespace TrapperProperties
		{
			const float c_maxHealthPoints						= 100.0f; // The max amount of health points the dasher is given when spawned
			const float c_shootingRate							= 2.0f; // The rate that trapper's will fire their traps 
		}
	}

	namespace Fonts
	{
		const sf::String c_UIFontAddress						= "Assets/Fonts/pixel_font.ttf"; // File path of the font used
	}

	namespace HighScoreProperties
	{
		const float			c_maxTimeDisplayingWarningMessage	= 5.0f; // The maximum time to display the warning message

		const int			c_maxAmountOfEntries				= 20; // The maximum amount of entries to be stored for the high score
		const int			c_amountOfTypesOfDataStored			= 2; // The amount of types that is stored per entry
		const int			c_characterAmountRequired			= 4; // The amount of characters required
	}

	namespace MainMenuProperties
	{
		const int			c_maxAmountOfButtons				= 4; // The max amount of buttons on the screen


		const sf::Vector2f	c_helpScreenPosition				= sf::Vector2f( 400.0f , 400.0f ); // The position of the help screen
	}

	namespace ParticleProperties
	{
		const float c_particleSpeed								= 500; // Constant Particle speed

		const int c_maxAmountOfStarParticles					= 20; // Max amount of star particles
	}

	namespace PlayerProperties
	{
		const float c_healingPoints								= 50.0f; // The amount of health points will be given
		const float c_maxHealth									= 100.0f; // The max amount of health points is given to the player when the game starts
		const float c_rapidFireShootingRate						= 0.1f; // The shooting rate for rapid fire
		const float c_maxTimeForRapidFireActivation				= 5.0f; // The max time the rapid fire power up can be active
		const float c_maxTimeForShieldActivation				= 10.0f; // The max time the shiled power up can be active
		const float c_positionY									= 650.0f; // The Y position for the player
		const float c_rapidFireProjectileOffsetPosition			= 12.0f; // The offset from the player to spawn the projectile on both side of the ship
		const float c_speed										= 0.5f; // The speed of the player

		const int	c_maxLives									= 3; // The max amount of lives given to the player when the game starts 

		namespace Animations
		{
			const float c_healingAnimationFrameRate				= 0.05f; // The frame rate for healing animation
			const float c_respawningAnimationFrameRate			= 0.05f; // The frame rate for respawning animation

			const int	c_maxFramesForHealingAnimation			= 20; // Max frames for healing animation
			const int	c_maxFramesForMovingAnimation			= 5; // Max frames for moving animation
			const int	c_maxFramesForRespawningAnimation		= 10; // Max frames for respawning animation
			const int	c_textureMovingCoordinateY				= 0; // Texture cooridante on the Y axis for moving animation
			const int	c_textureHealingCoordinateY				= 32; // Texture cooridante on the Y axis for healing animation
			const int	c_textureRespawningCoordinateY			= 64; // Texture cooridante on the Y axis for respawning animation
			const int	c_textureShieildingCoordinateY			= 96; // Texture cooridante on the Y axis for shielding animation
		}
	}

	namespace Positions
	{
		const float c_highestPointToDespawn						= -40.0f; // The highest position objects can go
		const float c_leftBoundaryPositionX						= 100.0f; // The boundary on the left where the player can go
		const float	c_lowestPointToDespawn						= 840.0f; // The lowest position objects can go
		const float c_rightBoundaryPositionX					= 700.0f; // The boundary on the right where the player can go
	}

	namespace ProgressionBarsProperties
	{
		const float c_maxProgressionBarHeight					= 48.0f; // The max height of the progression bar

		namespace PlayerHealthBar
		{
			const sf::Vector2f	c_playerHealthBarFillPosition	= sf::Vector2f( 3.0f , 751.0f ); // Position of the player's health fill bar
			const sf::Vector2f c_playerHealthBarPosition		= sf::Vector2f( 53.0f , 775 ); // Position of the player's health bar
		}

		namespace PowerUpBar
		{
			const float			c_shieldPointsRequired			= 100.0f; // The required amount of power up points to use shields
			const float			c_healingPointsRequired			= 205.0f; // The required amount of power up points to use healing
			const float			c_maxPowerUpPoints				= 310.0f; // The required amount of power up points that is allowed


			const sf::Vector2f	c_powerUpBarFillPosition		= sf::Vector2f( 493.0f , 751.0f ); // Position of the power up fill bar
			const sf::Vector2f	c_powerUpBarPosition			= sf::Vector2f( 645.0f , 775.0f ); // Position of the player's power up bar
		}
	}

	namespace ProjectileProperties
	{
		const int		c_maxAmountOfProjectiles				= 50; // The max amount of projectiles

		namespace PlayerProjectiles
		{
			const float c_damage								= 10.0f; // The damage player projectiles will deal
			const float c_speed									= 1000.0f; // The speed of player projectiles

			const int	c_maxAmountOfProjectiles				= 15; // The max projectiles the player will have
		}

		namespace EnemyProjectiles
		{
			const float c_damage								= 10.0f; // The damage enemy projectiles will deal
			const float c_speed									= 1000.0f; // The speed of enemy projectiles

			const int	c_maxAmountOfProjectiles				= 5; // The max amount of projectiles the enemies will have
		}

		namespace RapidFireProjectiles
		{
			const float c_damage								= 10.0f; // The damage rapid fire projectiles will deal
			const float c_speed									= 2000.0f; // The speed of enemy projectiles

			const int	c_maxAmountOfProjectiles				= 20; // The max projectiles for rapid fire
		}
	}

	namespace TextProperties
	{
		const float		   c_scoreEntryOffset					= 150.0f; // The offest of where the score entry will be positioned
		const float		   c_entryPositionXIncrementor			= 500.0f; // The incrementor on the position X to position the other half onto next side of the screen
		const float		   c_entryPositionYIncrementor			= 30.0f; // The incrementor on the position Y of each entry

		const sf::Vector2f c_gameOverMessageTextPosition		= sf::Vector2f( 400 , 200 ); // The position of the game over message
		const sf::Vector2f c_livesTextPosition					= sf::Vector2f( 50 , 735 ); // The position of the lives text
		const sf::Vector2f c_nameEnteredTextPosition			= sf::Vector2f( 400 , 250 ); // The position of the name entered
		const sf::Vector2f c_pressEscapeTextPosition			= sf::Vector2f( 400 , 700 ); // The position of the press escape text
		const sf::Vector2f c_scoreTextPosition					= sf::Vector2f( 400 , 20 ); // The position of the scores text
		const sf::Vector2f c_startingScoreTableEntryPosition	= sf::Vector2f( 100 , 200 ); // The position of the score table entry
		const sf::Vector2f c_titleScreenTextPosition			= sf::Vector2f( 400 , 20 ); // The position of title screens
		const sf::Vector2f c_warningMessageTextPosition			= sf::Vector2f( 400 , 300 ); // The position of the warning message
	}

	namespace TextureProperties
	{
		const float	c_maxGeneralAnimationFramesPerSecond		= 0.1f; // The general max frame rate for animations

		const int	c_spriteFrameSizeXY							= 32; // The frame size of all sprite frame
		const int	c_spriteOriginPositionXY					= 16; // The origin position of the sprite frame

	}

	namespace TextureFiles
	{
		// The file addresses of all textures used in the game
		const sf::String c_biterEnemyTextureAddress				= "Assets/Textures/enemy_biter.png";
		const sf::String c_dasherEnemyTextureAddress			= "Assets/Textures/enemy_dasher.png";
		const sf::String c_fighterEnemyTextureAddress			= "Assets/Textures/enemy_fighter.png";
		const sf::String c_helpScreenTextureAddress				= "Assets/Textures/help_screen.png";
		const sf::String c_playerHealthBarTextureAddress		= "Assets/Textures/player_health_bar.png";
		const sf::String c_playerPowerUpBarTextureAddress		= "Assets/Textures/player_power_up_bar.png";
		const sf::String c_playerTextureAddress					= "Assets/Textures/player_ship.png";
		const sf::String c_projectileEnemyTextureAddress		= "Assets/Textures/projectile_enemy.png";
		const sf::String c_projectilePlayerTextureAddress		= "Assets/Textures/projectile_player.png";
		const sf::String c_projectileRapidPlayerTextureAddress	= "Assets/Textures/projectile_rapid_player.png";
		const sf::String c_starTextureAddress					= "Assets/Textures/particles_star.png";
	}

	namespace Window
	{
		const int c_windowHeight	= 800; //The height size of the game window
		const int c_windowWidth		= 800; //The width size of the game window
	}
}

#endif // !SETTINGS_H
