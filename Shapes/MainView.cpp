#include "stdafx.h"
#include "MainView.h"
#include "RectangleShapeView.h"
#include "TriangleShapeView.h"
#include "EllipseShapeView.h"
#include "Scale9GridTexturedImage.h"
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

	auto texture = make_shared<sf::Texture>();
	texture->loadFromFile("images/btn1-normal.png");
	auto background = make_shared<CScale9GridTexturedImage>(texture, sf::IntRect(2, 2, 6, 6));
	background->SetSize(50, 50);
	toolbar->SetButtonsBackgrounds(background);

	toolbar->SetFrame({ 5, 50, 500, 50 });
	AppendChild(toolbar);
}

void  CMainView::CreateCanvas()
{
	m_canvas = CCanvas::Create(sf::FloatRect(50, 150, 550, 300));
	AppendChild(m_canvas->GetSheet());

	auto rect = make_shared<CRectangleShapeView>(sf::FloatRect(150, 300, 50, 30));
	m_canvas->Insert(rect, 1);
	
	auto triangle = make_shared<CTriangleShapeView>(sf::FloatRect(170, 300, 160, 170));
	m_canvas->Insert(triangle, 2);

	auto ellipse = make_shared<CEllipseShapeView>(sf::FloatRect(175, 200, 70, 100));
	m_canvas->Insert(ellipse, 3);

	auto rect2 = make_shared<CRectangleShapeView>(sf::FloatRect(200, 200, 100, 100));
	m_canvas->Insert(rect2, 0);

	AppendChild(m_canvas->GetSheet());
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
