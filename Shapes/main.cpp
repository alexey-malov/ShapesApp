// Shapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Button.h"
#include <iostream>
#include "ToolBar.h"

using namespace std;
using namespace ui;

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	auto button = ui::CButton::Create();
	auto button1 = ui::CButton::Create();

	auto toolbar = ui::CToolBar::Create(window.getSize());
	toolbar->AddChildWithIndex(button, 1);
	toolbar->AddChildWithIndex(button1, 2);

	toolbar->SetFrame({ 5, 50, 500, 50 });


	//auto root = make_shared<ui::CBaseControl>();
	//auto button = make_shared<ui::CButton>();
	//button->SetFrame({10, 10, 300, 100});
	//root->SetFrame({5, 50, 45, 80});
	//root->InsertChild(button);

	boost::signals2::scoped_connection con = button->DoOnClick([](){std::cout << "click" << std::endl; });
	boost::signals2::scoped_connection con2 = button1->DoOnClick([]() {std::cout << "clack" << std::endl; });

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
				toolbar->OnEvent(event);
				//root->OnEvent(event);
			}
		}

		window.clear();

		{
			//window.draw(*button);
			window.draw(*toolbar);
			//window.draw(*root);
		}

		window.display();
	}
	return 0;
}

