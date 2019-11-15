#include "Projectile.h"

Projectile::Projectile(const v2f& _vel, float _rad, const v2f& _pos) : m_velocity{_vel}, m_position{_pos}
{
	m_shape.setRadius(_rad);
	m_shape.setOrigin(v2f{ _rad, _rad });
	m_shape.setFillColor(sf::Color::White);
	m_shape.setPosition(m_position);
}

void Projectile::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_shape);
}
