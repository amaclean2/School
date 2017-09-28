#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;

const int HEIGHT = 600;
const int WIDTH = 800;

void run()
{

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Particles");
	window.setFramerateLimit(60);
	sf::CircleShape shape(2);
	shape.setPosition(WIDTH / 2, HEIGHT / 2);
	shape.setFillColor(sf::Color::White);

	while (window.isOpen())
	{
		
		shape.move(0, 1);


		sf::Event event;

		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
}

int main()
{
	run();

	return 0;
}