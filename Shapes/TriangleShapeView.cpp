#include "stdafx.h"
#include "TriangleShapeView.h"


namespace ui
{

CTriangleShapeView::CTriangleShapeView(sf::FloatRect const & frame)
	: CShapeView()
{
	InitTriangle();
	SetFrame(frame);
}

void CTriangleShapeView::OnFrameChanged(const sf::FloatRect & newFrame)
{
	sf::Vector2f size({ newFrame.width, newFrame.height });
	m_triangle.setPoint(0, { size.x / 2.f, 0.f });
	m_triangle.setPoint(1, { size.x, size.y });
	m_triangle.setPoint(2, { 0.f, size.y });

	m_triangle.setPosition({ newFrame.left, newFrame.top });
}

bool CTriangleShapeView::HitTest(sf::Vector2f const & local) const
{
	sf::Vector2f a = m_triangle.getPoint(0);
	sf::Vector2f b = m_triangle.getPoint(1);
	sf::Vector2f c = m_triangle.getPoint(2);
	sf::FloatRect frame = GetFrame();
	sf::Vector2f originSize({ frame.width / 2.f, frame.height / 2.f });
	a = { frame.left, frame.top - originSize.y };
	b = { frame.left + b.x - originSize.x,  frame.top + b.y - originSize.y };
	c = { frame.left + c.x - originSize.x, frame.top + c.y - originSize.y };

	return (((local.x - a.x)*(b.y - a.y) - (local.y - a.y)*(b.x - a.x)) <= 0 &&
		((local.x - b.x)*(c.y - b.y) - (local.y - b.y)*(c.x - b.x)) <= 0 &&
		((local.x - a.x)*(c.y - a.y) - (local.y - a.y)*(c.x - a.x)) >= 0);
}

void CTriangleShapeView::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_triangle, states);
}

void CTriangleShapeView::InitTriangle()
{
	m_triangle.setPointCount(3);
	m_triangle.setFillColor(sf::Color::Red);
	m_triangle.setOutlineThickness(2.f);
	m_triangle.setOutlineColor(sf::Color::Black);
}

}