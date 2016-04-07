// Shapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Button.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	auto button = ui::CButton::Create();

	std::shared_ptr<sf::Texture> background = std::make_shared<sf::Texture>();
	background->loadFromFile("./images/wood.jpg");
	button->SetBackground(background);
	background->loadFromFile("./images/stainless-steel.jpg");

	boost::signals2::scoped_connection con = button->DoOnClick([](){std::cout << "click" << std::endl; });

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
				button->OnEvent(event);
			}
		}

		window.clear();

		{
			window.draw(*button);
		}

		window.display();
	}
	return 0;
}

