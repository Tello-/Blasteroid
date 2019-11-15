#include "Ship.h"

Ship::Ship()
{
	m_shape.setPointCount(3);
	m_shape.setFillColor(sf::Color::Transparent);
	m_shape.setOutlineColor(sf::Color::White);
	m_shape.setOutlineThickness(-1.f);
	m_shape.setPoint(0, sf::Vector2f{  0.0f, 0.0f });
	m_shape.setPoint(1, sf::Vector2f{ 32.0f,16.0f });
	m_shape.setPoint(2, sf::Vector2f{ 0.0f, 32.0f });
	m_shape.setOrigin(12.f,16.f); // this is circumcenter of the triangle
	m_shape.setPosition(sf::Vector2f{ 300,300 });

}

void Ship::update(float _dt)
{
	if (isThrusting())
	{ // why is my ship decelerating almost immediately? before it wasn't. Let me change the deceleration value
		pApplyThrust(_dt);
	}
	m_shape.move(m_velocity);
	std::cout << "V= " << m_velocity.x << ", " << m_velocity.y << std::endl;
	m_velocity.x *= (m_deceleration);
	m_velocity.y *= (m_deceleration);
	if (abs(m_velocity.x) > 0.f && abs(m_velocity.x) < .1f) m_velocity.x = 0.f;
	if (abs(m_velocity.y) > 0.f && abs(m_velocity.y) < .1f) m_velocity.y = 0.f;

	pApplyRotation(_dt);
	
	

	/* ::::::::::::Bounding Box Debug Code:::::::::::::::::::::::*/
	/*shipBoundsShape.setFillColor(sf::Color::Transparent);
	shipBoundsShape.setOutlineColor(sf::Color::Red);
	shipBoundsShape.setOutlineThickness(1.f);
	

	shipBox = boundingBox();
	shipBoundsShape.setSize(v2f{ shipBox.width, shipBox.height });
	shipBoundsShape.setOrigin(v2f{ shipBox.width / 2, shipBox.height / 2 });*/
	//shipBoundsShape.setPosition(shipBox.left, shipBox.top);
	
	
	
	std::cout << "\t\tBounds: [" << shipBox.left << ", " << shipBox.top << std::endl;

	shipCenterShape.setFillColor(sf::Color::Green);
	shipCenterShape.setRadius(2.f);
	shipCenterShape.setOrigin(shipCenterShape.getRadius(), shipCenterShape.getRadius());
	shipCenterShape.setPosition(m_shape.getPosition());
	/* ::::::::::::end/Bounding Box Debug Code:::::::::::::::::::::::*/
}

void Ship::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	
	_target.draw(m_shape);
	_target.draw(shipBoundsShape);
	_target.draw(shipCenterShape);
	
}

float Ship::pDegreeToRadian(float _degree)
{
	return _degree * (M_PI / 180);
}

void Ship::pApplyThrust(float _dt)
{
	if (m_velocity.x >= MAX_VELOCITY)
	{
		m_velocity.x = MAX_VELOCITY;
	}
	else if (m_velocity.x <= MIN_VELOCITY)
	{
		m_velocity.x = MIN_VELOCITY;
	}
	else
	{
		m_velocity.x += cos(pDegreeToRadian(m_shape.getRotation())) * m_acceleration * _dt;
	}
	
	if (m_velocity.y >= MAX_VELOCITY)
	{
		m_velocity.y = MAX_VELOCITY;
	}
	else if (m_velocity.y <= MIN_VELOCITY)
	{
		m_velocity.y = MIN_VELOCITY;
	}
	else
	{
		m_velocity.y += sin(pDegreeToRadian(m_shape.getRotation())) * m_acceleration * _dt;
	}
}

void Ship::pApplyRotation(float _dt)
{

	m_shape.rotate(m_rotationalVelocity * m_currentRotationDirection * _dt);
}
