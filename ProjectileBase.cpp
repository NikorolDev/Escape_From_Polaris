#include "Helpers.h"
#include "ProjectileBase.h"

//#include <iostream>

ProjectileBase::ProjectileBase()
// Setting these variables before the constructor gets called
	: m_isAlive			( false )
	, m_damage			( 0.0f )
	, m_speed			( 0.0f )
	, m_projectileType	( ProjectileTypes::DefaultProjectile )
{	
	// Set the collider radius for every projectile
	m_circleCollider.setCircleColliderRadius( 7.0f );
}

void ProjectileBase::update(float deltaTime)
{
	// Move the projectile in that direction and set the position of the collider mathcing the porjectile
   	move(m_direction * m_speed * deltaTime);
	m_circleCollider.setPosition(getPosition());
}

void ProjectileBase::render( sf::RenderTarget* targetWindow )
{
	// If in debug mode render the circle collider
#ifdef _DEBUG
	m_circleCollider.render( targetWindow );
#endif

	// Render the projectile onto the screen
	targetWindow->draw( *this );
}

void ProjectileBase::setProjectileType(const ProjectileTypes& projectileType)	{ m_projectileType = projectileType; }

const ProjectileTypes& ProjectileBase::getProjectileType() const				{ return m_projectileType; }

void ProjectileBase::setIsProjectileAlive(bool isProjectileAlive)				{ m_isAlive = isProjectileAlive; }

const bool ProjectileBase::getIsProjectileAlive() const							{ return m_isAlive; }

void ProjectileBase::setDamage( float damage )									{ m_damage = damage; }

const float ProjectileBase::getDamage() const									{ return m_damage; }

void ProjectileBase::setProjectileSpeed(float projectileSpeed)					{ m_speed = projectileSpeed; }

void ProjectileBase::setProjectileDirection(float projectileDirectionX, float projectileDirectionY)
{
	m_direction.x = projectileDirectionX;
	m_direction.y = projectileDirectionY;
}

CircleCollider& ProjectileBase::getCircleCollider()								{ return m_circleCollider; }
