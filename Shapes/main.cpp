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
	auto toolbar = ui::CToolBar::Create(size);
	toolbar->AddChildWithIndex(1);
	toolbar->AddChildWithIndex(2);
	toolbar->AddChildWithIndex(3);

	auto button1 = toolbar->GetButton(1);
	auto button2 = toolbar->GetButton(2);
	auto button3 = toolbar->GetButton(3);

	button1->SetAction([]() {std::cout << "click" << std::endl; });
	button2->SetAction([]() {std::cout << "clack" << std::endl; });
	button3->SetAction([]() {std::cout << "bang" << std::endl; });

	std::shared_ptr<sf::Texture> background = std::make_shared<sf::Texture>();
	background->loadFromFile("./images/wood.jpg");
	toolbar->SetButtonsBackgrounds(background);

	toolbar->SetFrame({ 5, 50, 500, 50 });
	parent.AppendChild(toolbar);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
	window.setFramerateLimit(30);

	sf::View view(window.getDefaultView());

	auto root = CBaseControl::Create();
	AppendToolbar(*root, sf::Vector2u(490, 500));

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

				if (event.type == sf::Event::Resized)
				{
					view = sf::View(sf::FloatRect(0.f, 0.f,
						float(window.getSize().x),
						float(window.getSize().y)));
					window.setView(view);
				}
			}
		}

		window.clear();
		window.draw(*root);
		window.display();
	}
	return 0;
}

