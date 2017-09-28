#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;

const int HEIGHT = 600;
const int WIDTH = 800;
const int CIRCLESIZE = 20;
const int RIGHT = WIDTH - (CIRCLESIZE * 2);
const int LEFT = 0;
const int BOUNCE = 2;
const int BOTTOM = HEIGHT - (CIRCLESIZE * 2);

double vel(double pos, double top)
{
	pos -= top;
	if (BOTTOM == top)
		return 0;
	else
		return 0.15 * (pos + 15);
}

void gravity(double& top)
{
	double middle = top;
	if (BOTTOM - top < 1)
		top = BOTTOM;
	else
	{
		middle = (BOTTOM - top) / BOUNCE;
		top += middle;
	}
}

void run()
{
	double Hspeed = 5;
	double drag = .98;
	int posX;
	bool down = true;
	bool ri = true;
	int followPosX;
	int followPosY = 0;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Bouncy Ball");
	window.setFramerateLimit(60);
	sf::CircleShape shape(CIRCLESIZE);
	shape.setPosition(10, BOTTOM);
	shape.setFillColor(sf::Color::Red);

	double posY = shape.getPosition().y;
	double top = posY;

	while (window.isOpen())
	{
		sf::Event event;
		posX = shape.getPosition().x;
		posY = shape.getPosition().y;

		//verticle movement
		if (down)
		{
			if (posY >= BOTTOM)
			{
				down = false;
				gravity(top);
			}
			shape.move(0, vel(posY, top));
		}

		else
		{
			if (posY <= top)
				down = true;
			shape.move(0, -vel(posY, top));
		}

		//horizontal movement
		if (vel(posY, top) == 0)
			Hspeed *= drag;

		if (ri)
		{
			if (posX >= RIGHT)
				ri = false;
			shape.move(Hspeed, 0);
		}
		else
		{
			if (posX <= LEFT)
				ri = true;
			shape.move(-Hspeed, 0);
		}

		sf::Vector2i mousePos;
		bool clickedOnBall = false;

		while (window.pollEvent(event))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (sf::Mouse::getPosition(window).x >= posX &&
					sf::Mouse::getPosition(window).x <= (posX + (2 * CIRCLESIZE)))
				{
					if (sf::Mouse::getPosition(window).y >= posY &&
						sf::Mouse::getPosition(window).y <= (posY + (2 * CIRCLESIZE)))
						clickedOnBall = true;
				}

				followPosX = posX;
				followPosY = posY;

				shape.setPosition(sf::Mouse::getPosition(window).x -
					CIRCLESIZE, sf::Mouse::getPosition(window).y - CIRCLESIZE);
			}
			clickedOnBall = false;
			if (event.type == sf::Event::MouseButtonReleased)
			{

				if (posY < followPosY)
				{
					top = (posY - (followPosY - posY)) * 1.15;
					if (top < 1 || top > posY)
						top = 1;
					down = false;
				}
				else
				{
					top = followPosY * 1.15;
					if (top < 1 || top > posY)
						top = 1;
					down = true;
				}

				if (posX > followPosX)
				{
					ri = true;
					Hspeed = (posX - followPosX) / 3;
				}
				else
				{
					ri = false;
					Hspeed = -(posX - followPosX) / 3;
				}
			}

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