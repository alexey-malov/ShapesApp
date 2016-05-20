#include "stdafx.h"
#include "RectangleShapeView.h"

namespace ui
{

CRectangleShapeView::CRectangleShapeView(sf::FloatRect const & frame)
	: CShapeView(frame)
	, m_frame(frame)
{
	InitRectangle();
}

void CRectangleShapeView::OnFrameChanged(const sf::FloatRect & newFrame)
{
	m_frame = newFrame;
	m_rectangle.setSize({ m_frame.width, m_frame.height });
	m_rectangle.setOrigin({ m_frame.width / 2.f, m_frame.height / 2.f });
	m_rectangle.setPosition({ m_frame.left, m_frame.top });
}

void CRectangleShapeView::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_rectangle, states);
}

void CRectangleShapeView::InitRectangle()
{
	OnFrameChanged(m_frame);
	m_rectangle.setOutlineThickness(2.f);
	m_rectangle.setOutlineColor(sf::Color::Black);
	m_rectangle.setFillColor(sf::Color::Green);
}

}
