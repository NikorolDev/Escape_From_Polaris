#include "GameText.h"
#include "Helpers.h"
#include "HUD.h"
#include "LivesText.h"
#include "Player.h"
#include "PlayerHealthBar.h"
#include "PowerUpBar.h"
#include "ScoresText.h"
#include "TextureManager.h"

HUD::HUD()
// Setting the player to null pointer
	: m_pPlayer			( nullptr )
{
	// Make an instance for progression bars of the health and power up
	m_pPlayerHealthBar	= new PlayerHealthBar();
	m_pPowerUpBar		= new PowerUpBar();

	// Make an instance for game texts of the scores and lives
	m_pLivesText		= new LivesText();
	m_pScoreText		= new ScoresText();
}

HUD::~HUD()
{
	// Delete all the objects that were created as new
	safeDeletePointer( m_pScoreText );
	safeDeletePointer( m_pLivesText );
	safeDeletePointer( m_pPowerUpBar );
	safeDeletePointer( m_pPlayerHealthBar );
}

void HUD::initialise( Player* pPlayer , TextureManager* pTextureManager )
{
	// Set the player
	m_pPlayer			= pPlayer;

	// load the texture and set it to the player's health bar and power up bar
	m_pPlayerHealthBar->loadSpriteTexture	( pTextureManager->getTexture( GameTextures::HealthBarTexture ) , false );
	m_pPowerUpBar->loadSpriteTexture		( pTextureManager->getTexture( GameTextures::PowerUpBarTexture ) , false );

	// Iniitalise the lives and scores text
	m_pLivesText->initialise				( m_pPlayer );
	m_pScoreText->initialise				( m_pPlayer );
}

void HUD::update()
{
	// Update the power up bar using player's power up points and the health bar using player's health points
	m_pPlayerHealthBar->update	( m_pPlayer->getHealthPoints() );
	m_pPowerUpBar->	update		( m_pPlayer->getPowerUpPoints() );
}

void HUD::render( sf::RenderTarget* targetWindow )
{
	// Render the HUD elements
	m_pPlayerHealthBar->render	( targetWindow );
	m_pPowerUpBar->render		( targetWindow );
	m_pLivesText->render		( targetWindow );
	m_pScoreText->render		( targetWindow );
}
