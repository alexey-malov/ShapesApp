#include "stdafx.h"
#include "MainView.h"
#include <iostream>

using namespace ui;
using namespace std;
using namespace sf;

shared_ptr<CMainView> CMainView::Create()
{
	return shared_ptr<CMainView>(new CMainView());
}

void CMainView::AddChildWithIndex(unsigned index, Vector2u const &size)
{
	auto toolbar = CToolBar::Create(size);

	InsertChildAtIndex(toolbar, index);

	m_toolbars.emplace(index, toolbar);
}

shared_ptr<CToolBar> CMainView::GetToolbar(unsigned index)
{
	return m_toolbars.at(index);
}

void CMainView::CreateMainToolbar()
{
	AddChildWithIndex(0, sf::Vector2u(490, 500));

	auto toolbar = GetToolbar(0);

	toolbar->SetRightIndentSize(float(500u - 490u));

	auto createRectangleButton = toolbar->AddChildWithIndex(1);
	auto createTriangleButton = toolbar->AddChildWithIndex(2);
	auto createCircleButton = toolbar->AddChildWithIndex(3);
	auto undoButton = toolbar->AddChildWithIndex(4);
	auto redoButton =toolbar->AddChildWithIndex(5);
	auto deleteButton = toolbar->AddChildWithIndex(6);

	std::shared_ptr<sf::Texture> rectangleTexture = std::make_shared<sf::Texture>();
	std::shared_ptr<sf::Texture> triangleTexture = std::make_shared<sf::Texture>();
	std::shared_ptr<sf::Texture> circleTexture = std::make_shared<sf::Texture>();
	std::shared_ptr<sf::Texture> undoTexture = std::make_shared<sf::Texture>();
	std::shared_ptr<sf::Texture> redoTexture = std::make_shared<sf::Texture>();
	std::shared_ptr<sf::Texture> deleteTexture = std::make_shared<sf::Texture>();

	rectangleTexture->loadFromFile("./images/icons/rectangle.png");
	triangleTexture->loadFromFile("./images/icons/triangle.png");
	circleTexture->loadFromFile("./images/icons/circle.png");
	undoTexture->loadFromFile("./images/icons/undo.png");
	redoTexture->loadFromFile("./images/icons/redo.png");
	deleteTexture->loadFromFile("./images/icons/delete.png");

	createRectangleButton->SetIcon(rectangleTexture);
	createTriangleButton->SetIcon(triangleTexture);
	createCircleButton->SetIcon(circleTexture);
	undoButton->SetIcon(undoTexture);
	redoButton->SetIcon(redoTexture);
	deleteButton->SetIcon(deleteTexture);


	createRectangleButton->SetAction([]() {cout << "Rectangle created" << endl; });
	createTriangleButton->SetAction([]() {cout << "Triangle created" << endl; });
	createCircleButton->SetAction([]() {cout << "Circle created" << endl; });
	undoButton->SetAction([]() {cout << "Undo" << endl; });
	redoButton->SetAction([]() {cout << "Redo" << endl; });
	deleteButton->SetAction([]() {cout << "delete shape" << endl; });

	shared_ptr<Texture> background = make_shared<Texture>();
	background->loadFromFile("./images/wood.jpg");
	toolbar->SetButtonsBackgrounds(background);

	toolbar->SetFrame({ 5, 50, 500, 50 });
	AppendChild(toolbar);
}

void  CMainView::CreateCanvas()
{
	m_canvas = CCanvas::Create(sf::Vector2u(550, 300));

	m_canvas->SetCanvasPosition(sf::Vector2f(50, 150));
	InsertChildAtIndex(m_canvas, 2);
}

bool CMainView::OnWindowResized(sf::Event::SizeEvent const & event)
{
	for (auto it : m_toolbars)
	{
		it.second->SetToolbarSize({ float(event.width) 
			- it.second->GetRightIndentSize()
			, it.second->GetToolbarSize().y });
	}
	m_canvas->SetCanvasSize({float(event.width), float(event.height)});

	return true;
}
