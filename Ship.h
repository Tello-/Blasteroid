#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

using v2f = sf::Vector2f;

class Ship : public sf::Drawable
{
public:
	Ship();

	enum ShipCommand{HALT_THRUST, THRUST, ROTATE_CW, ROTATE_CCW, FIRE};
	enum RotationDirection{ CCW = -1, NONE, CW};
	void update(float _dt);
	void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;

	/* ::::::::::::: SHIP COMMANDS ::::::::::::::::*/
	void haltThrust() { m_isThrusting = false; }
	void thrust() { m_isThrusting = true; }
	void rotateCW() { m_currentRotationDirection = RotationDirection::CW; }
	void rotateCCW() { m_currentRotationDirection = RotationDirection::CCW; }
	void haltRotation() { m_currentRotationDirection = NONE; }
	void fire() {}
	/* ::::::::::::::::::::::::::::::::::::::::::::*/

	bool isThrusting() const { return m_isThrusting; }	

	const sf::FloatRect& boundingBox() const { return m_shape.getGlobalBounds(); }

	void teleport(const v2f& _pos) { m_shape.setPosition(_pos); }
	const v2f& position() const { return m_shape.getPosition(); }

	

private:
	bool pIsMoving() const { return m_velocity.x != 0 && m_velocity.y != 0; }
	float pDegreeToRadian(float _degree);

	void pApplyThrust(float);
	void pApplyRotation(float);
	
	sf::ConvexShape m_shape;
	v2f m_velocity;
	const float MAX_VELOCITY{ 15.0f };
	const float MIN_VELOCITY{ -10.f };
	float m_currentRotation{ 0.f };
	RotationDirection m_currentRotationDirection{ NONE };


	float m_rotationalVelocity{ 200.f };
	float m_acceleration{ 10.f };
	float m_deceleration{ .99f };
	bool m_isThrusting{ false };


	sf::RectangleShape shipBoundsShape;
	sf::CircleShape shipCenterShape;
	sf::FloatRect shipBox;
};

