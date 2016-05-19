#include "stdafx.h"
#include "EllipseShapeView.h"

namespace ui
{

CEllipseShapeView::CEllipseShapeView(sf::FloatRect const & frame)
	: CShapeView(frame)
	, m_frame(frame)
{
	InitCircle();
}

void CEllipseShapeView::OnFrameChanged(const sf::FloatRect & newFrame)
{
	m_frame = newFrame;
	m_circle.setRadius(m_frame.width / 2.f); // TODO: calculate raduis from size
	m_circle.setOrigin({ m_frame.width / 2.f, m_frame.height / 2.f });
	m_circle.setPosition({ m_frame.left, m_frame.top });
}

bool CEllipseShapeView::HitTest(sf::Vector2f const & local) const
{
	sf::Vector2f diff = local - sf::Vector2f({ m_frame.left, m_frame.left });
	return std::pow(diff.x, 2) + std::pow(diff.y, 2) <= m_frame.width / 2.f * m_frame.height / 2.f;
}

void CEllipseShapeView::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_circle, states);
}

void CEllipseShapeView::InitCircle()
{
	OnFrameChanged(m_frame);
	m_circle.setFillColor(sf::Color::Yellow);
	m_circle.setOutlineThickness(2.f);
	m_circle.setOutlineColor(sf::Color::Black);
}

}