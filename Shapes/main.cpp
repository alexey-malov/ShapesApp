// Shapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Button.h"
#include <iostream>
#include "ToolBar.h"
#include "ResourceHolder.h"
#include "ResourceIdientificators.h"

using namespace std;
using namespace ui;

void AppendToolbar(CBaseControl & parent, const sf::Vector2u & size, const TextureHolder & textures)
{
	auto button = ui::CButton::Create();
	auto button1 = ui::CButton::Create();

	auto toolbar = ui::CToolBar::Create(size);
	toolbar->AddChildWithIndex(button, 1);
	toolbar->AddChildWithIndex(button1, 2);

	toolbar->SetFrame({ 5, 50, 500, 50 });
	button->SetBackground(std::make_shared<sf::Texture>(textures.Get(TexturesID::BackgroundFirst)));

	boost::signals2::scoped_connection con = button->DoOnClick([]() {std::cout << "click" << std::endl; });
	boost::signals2::scoped_connection con2 = button1->DoOnClick([]() {std::cout << "clack" << std::endl; });

	button->SetIcon(textures.Get(TexturesID::Icon));

	parent.AppendChild(toolbar);
}

int main()
{
	TextureHolder textures;
	textures.Load(TexturesID::BackgroundFirst, "./images/wood.jpg");
	textures.Load(TexturesID::BackgroundSecond, "./images/stainless-steel.jpg");
	textures.Load(TexturesID::Icon, "./images/test_icon.png");

	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");

	auto root = CBaseControl::Create();
	AppendToolbar(*root, window.getSize(), textures);

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

