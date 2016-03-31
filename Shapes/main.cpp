#include "stdafx.h"
#include <iostream>
#include "Button.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	ui::CButton button;
	button.setPosition({ 200.f, 200.f });
	button.setScale({ 2.f, 2.f });

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

