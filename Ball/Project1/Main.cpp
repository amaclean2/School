#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;

const int WIDTH = 800;
const int HEIGHT = (WIDTH * 9) / 16;

void openWindow()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works");
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
	}
	window.clear();
	window.draw(shape);
	window.display();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Works");
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
	}

	window.clear();
	window.draw(shape);
	window.display();

	return 0;
}