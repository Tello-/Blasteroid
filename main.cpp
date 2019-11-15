

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Projectile.h"

const unsigned WINDOW_X{ 600 };
const unsigned WINDOW_Y{ 600 };

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	Ship ship;
	//ship.setPosition(sf::Vector2f{ 50.f, 50.f });



	Projectile bullet{ sf::Vector2f{ 30.f, 0.f },2.f, sf::Vector2f{ 300.f + 16, 300.f} };


	float elapsed{ 0.0f };
	float fps{ 60.0f };
	float frametime{ 1.0f / 60.f };
	sf::Clock clock;
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) ship.rotateCCW();		
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) ship.rotateCW();
		else ship.haltRotation();
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) ship.thrust();
		else { ship.haltThrust(); }


		if (elapsed >= frametime)
		{
			
			ship.update(elapsed);

			if (ship.boundingBox().left + ship.boundingBox().width < 0) ship.teleport(sf::Vector2f(WINDOW_X, ship.position().y));
			if (ship.boundingBox().left > WINDOW_X) ship.teleport(sf::Vector2f(0, ship.position().y));
			if (ship.boundingBox().top + ship.boundingBox().height < 0) ship.teleport(sf::Vector2f(ship.position().y, WINDOW_Y));
			if (ship.boundingBox().top > WINDOW_Y) ship.teleport(sf::Vector2f(ship.position().x, 0));

			elapsed -= frametime;
		}
		window.clear();
		window.draw(ship);
		window.draw(bullet);

		
		window.display();
		elapsed += clock.restart().asSeconds();
	}

	return 0;
}