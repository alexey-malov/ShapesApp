#include "stdafx.h"
#include "RectangleShapeView.h"

CRectangleShapeView::CRectangleShapeView(sf::Vector2f const & size, sf::Vector2f const & pos)
	: CShapeView(size, pos)
{
	InitRectangle(size, pos);
}

void CRectangleShapeView::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_rectangle, states);
}

void CRectangleShapeView::SetSize(const sf::Vector2f & size)
{
	m_size = size;
	m_rectangle.setSize(m_size);
	m_rectangle.setOrigin({ m_size.x / 2.f, m_size.y / 2.f });
}

void CRectangleShapeView::SetPosition(const sf::Vector2f & position)
{
	m_position = position;
	m_rectangle.setPosition(m_position);
}

void CRectangleShapeView::InitRectangle(sf::Vector2f size, sf::Vector2f position)
{
	SetSize(size);
	SetPosition(position);
	m_rectangle.setOutlineThickness(2.f);
	m_rectangle.setOutlineColor(sf::Color::Black);
	m_rectangle.setFillColor(sf::Color::Green);
}
