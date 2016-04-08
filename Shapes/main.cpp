// Shapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Button.h"
#include <iostream>

using namespace std;
using namespace ui;

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");

	auto root = CBaseControl::Create();
	auto button = CButton::Create();
	button->SetFrame({10, 10, 300, 100});
	root->SetFrame({5, 50, 45, 80});
	root->AppendChild(button);

	boost::signals2::scoped_connection con = button->DoOnClick([](){std::cout << "click" << std::endl; });

	std::shared_ptr<sf::Texture> textureImage = std::make_shared<sf::Texture>();
	textureImage->loadFromFile("./images/test_icon.png");
	button->SetIcon(textureImage);

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
				root->OnEvent(event);
			}
		}

		window.clear();

		{
			window.draw(*root);
		}

		window.display();
	}
	return 0;
}

