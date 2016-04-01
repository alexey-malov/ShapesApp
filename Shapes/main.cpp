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

	auto root = make_shared<ui::CBaseControl>();
	auto button = make_shared<ui::CButton>();
	button->SetFrame({10, 10, 300, 100});
	root->SetFrame({5, 50, 45, 80});
	root->InsertChild(button);

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

