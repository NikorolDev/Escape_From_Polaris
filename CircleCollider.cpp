#include "CircleCollider.h"

CircleCollider::CircleCollider()
//Default initialisation of radius
	: m_isActive	( false )
	, m_radius		( 0.0f )
{
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::render(sf::RenderTarget* targetWindow)
{
	// Render the circle collider. This will only be rendered in Debug mode
	targetWindow->draw( *this );
}

void CircleCollider::setIsActive( bool isActive )	{ m_isActive = isActive; }

const bool CircleCollider::getIsActive() const		{ return m_isActive; }

void CircleCollider::setCircleColliderRadius( float radius )
{
	//Set the radius for the circle collider and set the origin to be in the middle of circle
	m_radius = radius;
	setRadius(m_radius);
	setOrigin(m_radius, m_radius);
}
