#include "ProgressionBar.h"
#include "Settings.h"

ProgressionBar::ProgressionBar()
// Setting these variables before the constructor gets called
	: m_minProgressValue ( 0.0f )
	, m_maxBarHeight	 ( 0.0f )
	, m_maxProgressValue ( 0.0f )
{
}

ProgressionBar::~ProgressionBar()
{
}

void ProgressionBar::update( float progressionValue )
{
	// Set the size of the progression bar fill, using the current progresion bar value
	m_progressBar.setSize( sf::Vector2f( progressionValue , m_maxBarHeight ) );
}

void ProgressionBar::render( sf::RenderTarget* targetWindow )
{
	// Redner the bar fill and the texture that is assigned to it, which would be set from the child classes
	targetWindow->draw( m_progressBar );
	targetWindow->draw( *this );
}

void ProgressionBar::setProgressBar( sf::Vector2f position , float initialWidth , float maxHeight , sf::Color barFillColour )
{
	// Set the max height to be used for resizing
	m_maxBarHeight = maxHeight;

	// Set the position, size and colour of fill bar
	m_progressBar.setPosition	( position );
	m_progressBar.setSize		( sf::Vector2f( initialWidth , m_maxBarHeight ) );
	m_progressBar.setFillColor	( barFillColour );
}

void ProgressionBar::setMaxProgressValue( float maxProgressValiue ) { m_maxProgressValue = maxProgressValiue; }

const float ProgressionBar::getMaxProgressValue() const				{ return m_maxProgressValue; }

void ProgressionBar::setMinProgressValue( float minProgressValue )	{ m_minProgressValue = minProgressValue; }

const float ProgressionBar::getMinProgressValue() const					{ return m_minProgressValue; }
