#include "stdafx.h"
#include "Canvas.h"

namespace ui
{

std::shared_ptr<CCanvas> CCanvas::Create(sf::Vector2u const & size)
{
	return std::shared_ptr<CCanvas>(new CCanvas(size));
}

void CCanvas::AppendShape(std::shared_ptr<CShapeView> && shape)
{
	m_shapes.emplace_back(move(shape));
}

CCanvas::CCanvas(sf::Vector2u const & size)
{
	m_background.setSize({ float(size.x), float(size.y) });
	m_background.setFillColor(sf::Color::White);
}

void CCanvas::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_background, states);
}

sf::Vector2f CCanvas::GetCanvasSize() const
{
	return m_background.getSize();
}

void CCanvas::SetCanvasSize(sf::Vector2f const & size)
{
	m_background.setSize(size);
}

sf::Vector2f CCanvas::GetCanvasPosition()const
{
	return m_background.getPosition();
}

void CCanvas::SetCanvasPosition(sf::Vector2f const &pos)
{
	m_background.setPosition(pos);
}

}