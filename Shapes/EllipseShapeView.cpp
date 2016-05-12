#include "stdafx.h"
#include "EllipseShapeView.h"


CEllipseShapeView::CEllipseShapeView(sf::Vector2f const & size, sf::Vector2f const & pos)
	: CShapeView(size, pos)
{
	InitCircle(size, pos);
}

void CEllipseShapeView::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_circle, states);
}

void CEllipseShapeView::SetSize(const sf::Vector2f & size)
{
	m_size = size;
	m_circle.setRadius(size.x / 2.f); // TODO: calculate raduis from size
	m_circle.setOrigin({ size.x / 2.f, size.y / 2.f });
}

void CEllipseShapeView::SetPosition(const sf::Vector2f & position)
{
	m_position = position;
	m_circle.setPosition(m_position);
}

void CEllipseShapeView::InitCircle(sf::Vector2f size, sf::Vector2f position)
{
	SetSize(size);
	SetPosition(position);
	m_circle.setFillColor(sf::Color::Yellow);
	m_circle.setOutlineThickness(2.f);
	m_circle.setOutlineColor(sf::Color::Black);
}