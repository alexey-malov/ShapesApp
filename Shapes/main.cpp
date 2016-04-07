// Shapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Button.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	ui::CButton button;

	std::shared_ptr<sf::Texture> textureImage;
	textureImage->loadFromFile("C://write.png");
	button.setIcon(textureImage);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else
			{
				button.OnEvent(event);
			}
		}

		window.clear();

		{
			window.draw(button);
		}

		window.display();
	}

	return 0;
}

