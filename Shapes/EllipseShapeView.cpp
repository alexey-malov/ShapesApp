#include "stdafx.h"
#include "EllipseShapeView.h"

namespace ui
{

CEllipseShapeView::CEllipseShapeView(sf::FloatRect const & frame)
	: CShapeView()
{
	SetFrame(frame);
	InitCircle();
}

void CEllipseShapeView::OnFrameChanged(const sf::FloatRect & newFrame)
{
	m_circle.setRadius(newFrame.width / 2.f); // TODO: calculate raduis from size
	m_circle.setPosition({ newFrame.left, newFrame.top });
}

bool CEllipseShapeView::HitTest(sf::Vector2f const & local) const
{
	sf::FloatRect frame = GetFrame();
	sf::Vector2f diff = local - sf::Vector2f({ frame.left, frame.left });
	return std::pow(diff.x, 2) + std::pow(diff.y, 2) <= frame.width / 2.f * frame.height / 2.f;
}

void CEllipseShapeView::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_circle, states);
}

void CEllipseShapeView::InitCircle()
{
	m_circle.setFillColor(sf::Color::Yellow);
	m_circle.setOutlineThickness(2.f);
	m_circle.setOutlineColor(sf::Color::Black);
}

}