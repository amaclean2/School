#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;

const int WIDTH = 600;
const int HEIGHT = 500;
const int CIRCLESIZE = 20;

void run()
{
	

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Bouncy Ball");
	window.setFramerateLimit(60);
	sf::CircleShape ball(CIRCLESIZE);
	ball.setFillColor(sf::Color::Blue);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(ball);
		window.display();
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}