// Shapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Button.h"
#include <iostream>
#include "ToolBar.h"

using namespace std;
using namespace ui;

void AppendToolbar(CBaseControl & parent, const sf::Vector2u & size)
{
	auto button = ui::CButton::Create();
	auto button1 = ui::CButton::Create();

	auto toolbar = ui::CToolBar::Create(size);
	toolbar->AddChildWithIndex(button, 1);
	toolbar->AddChildWithIndex(button1, 2);

	toolbar->SetFrame({ 5, 50, 500, 50 });

	std::shared_ptr<sf::Texture> background = std::make_shared<sf::Texture>();
	background->loadFromFile("./images/wood.jpg");
	button->SetBackground(background);
	background->loadFromFile("./images/stainless-steel.jpg");

	boost::signals2::scoped_connection con = button->DoOnClick([]() {std::cout << "click" << std::endl; });
	boost::signals2::scoped_connection con2 = button1->DoOnClick([]() {std::cout << "clack" << std::endl; });

	std::shared_ptr<sf::Texture> textureImage = std::make_shared<sf::Texture>();
	textureImage->loadFromFile("./images/test_icon.png");
	button->SetIcon(textureImage);

	parent.AppendChild(toolbar);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");

	auto root = CBaseControl::Create();
	AppendToolbar(*root, window.getSize());

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

