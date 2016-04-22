// Shapes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Button.h"
#include <iostream>
#include "Stage.h"
#include "MainView.h"

using namespace std;
using namespace sf;
using namespace ui;

int main()
{
	auto window = make_unique<sf::RenderWindow>(VideoMode(800, 600), "Shapes app");
	ui::CStage stage(move(window));
	auto mainView = CMainView::Create();
	mainView->CreateMainToolbar();
	stage.GetRoot()->AppendChild(mainView);
	stage.Execute();
	return 0;
}

