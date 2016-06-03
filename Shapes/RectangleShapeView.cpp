#include "stdafx.h"
#include "RectangleShapeView.h"

namespace ui
{

CRectangleShapeView::CRectangleShapeView(sf::FloatRect const & frame)
	: CShapeView()
{
	InitRectangle();
	SetFrame(frame);
}

void CRectangleShapeView::OnFrameChanged(const sf::FloatRect & newFrame)
{
	m_rectangle.setSize({ newFrame.width, newFrame.height });
	m_rectangle.setPosition({ newFrame.left, newFrame.top });
}

void CRectangleShapeView::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_rectangle, states);
}

void CRectangleShapeView::InitRectangle()
{
	m_rectangle.setOutlineThickness(2.f);
	m_rectangle.setOutlineColor(sf::Color::Black);
	m_rectangle.setFillColor(sf::Color::Green);
}

}
