#include "stdafx.h"
#include "TriangleShapeView.h"


CTriangleShapeView::CTriangleShapeView(sf::Vector2f const& size, sf::Vector2f const& pos)
	: CShapeView(size, pos)
{
	InitTriangle(size, pos);
}

void CTriangleShapeView::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_triangle, states);
}

void CTriangleShapeView::SetSize(const sf::Vector2f & size)
{
	m_size = size;
	m_triangle.setPoint(0, { m_size.x / 2.f, 0.f });
	m_triangle.setPoint(1, { m_size.x, m_size.y });
	m_triangle.setPoint(2, { 0.f, m_size.y });

	m_triangle.setOrigin({ m_size.x / 2.f, m_size.y / 2.f });
}

void CTriangleShapeView::SetPosition(const sf::Vector2f & position)
{
	m_position = position;
	m_triangle.setPosition(m_position);
}

void CTriangleShapeView::InitTriangle(sf::Vector2f size, sf::Vector2f position)
{
	m_triangle.setPointCount(3);
	SetSize(size);
	SetPosition(position);
	m_triangle.setFillColor(sf::Color::Red);
	m_triangle.setOutlineThickness(2.f);
	m_triangle.setOutlineColor(sf::Color::Black);
}
