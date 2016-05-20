#include "stdafx.h"
#include "TriangleShapeView.h"


namespace ui
{

CTriangleShapeView::CTriangleShapeView(sf::FloatRect const & frame)
	: CShapeView(frame)
	, m_frame(frame)
{
	InitTriangle();
}

void CTriangleShapeView::OnFrameChanged(const sf::FloatRect & newFrame)
{
	m_frame = newFrame;
	sf::Vector2f size({ m_frame.width, m_frame.height });
	m_triangle.setPoint(0, { size.x / 2.f, 0.f });
	m_triangle.setPoint(1, { size.x, size.y });
	m_triangle.setPoint(2, { 0.f, size.y });

	m_triangle.setOrigin({ size.x / 2.f, size.y / 2.f });
	m_triangle.setPosition({ m_frame.left, m_frame.top });
}

bool CTriangleShapeView::HitTest(sf::Vector2f const & local) const
{
	sf::Vector2f a = m_triangle.getPoint(0);
	sf::Vector2f b = m_triangle.getPoint(1);
	sf::Vector2f c = m_triangle.getPoint(2);
	sf::Vector2f originSize({ m_frame.width / 2.f, m_frame.height / 2.f });
	a = { m_frame.left, m_frame.top - originSize.y };
	b = { m_frame.left + b.x - originSize.x,  m_frame.top + b.y - originSize.y };
	c = { m_frame.left + c.x - originSize.x, m_frame.top + c.y - originSize.y };

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
	OnFrameChanged(m_frame);
	m_triangle.setFillColor(sf::Color::Red);
	m_triangle.setOutlineThickness(2.f);
	m_triangle.setOutlineColor(sf::Color::Black);
}

}