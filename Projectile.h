#pragma once
#include <SFML/Graphics.hpp>

using v2f = sf::Vector2f;

class Projectile : public sf::Drawable
{
public:
	Projectile(const v2f& _vel, float _rad, const v2f& _pos = v2f{});

	void draw(sf::RenderTarget&, sf::RenderStates) const;
protected:
	v2f m_position;
	v2f m_velocity;
	sf::CircleShape m_shape;
};

