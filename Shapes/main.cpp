// Shapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Button.h"
#include "Scale9GridTexturedImage.h"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	auto button = ui::CButton::Create();
	auto texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("texture.jpg");
	auto ninePatch = std::make_shared<CScale9GridTexturedImage>(texture, sf::IntRect(33, 0, 9, 35));
	ninePatch->SetSize(200, 36);
	boost::signals2::scoped_connection con = button->DoOnClick([](){std::cout << "click" << std::endl; });
	button->SetBackground(ninePatch);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
			{
				std::cout << "Q" << std::endl;
			}
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
			//window.draw(*ninePatch);
		}

		window.display();
	}
	return 0;
}

