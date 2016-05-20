#include "stdafx.h"
#include "Canvas.h"
#include <iostream>

namespace ui
{

std::shared_ptr<CCanvas> CCanvas::Create(sf::FloatRect const& frame)
{
	return std::shared_ptr<CCanvas>(new CCanvas(frame));
}

void CCanvas::Insert(std::shared_ptr<CShapeView> const & shape, unsigned index)
{
	if (index >= m_shapes.size())
	{
		m_shapes.resize(index + 1);
	}
	m_shapes[index] = shape;
	m_sheet->InsertChildAtIndex(shape, index);
}

std::shared_ptr<CShapeView> CCanvas::GetShape(unsigned index)
{
	assert(index >= m_shapes.size());
	return m_shapes[index];
}

CCanvas::CCanvas(sf::FloatRect const& frame)
	: m_sheet(ui::CSheet::Create(frame))
{
}

void CCanvas::SetCanvasSize(sf::Vector2f const & size)
{
	m_sheet->SetSheetSize(size);
}

void CCanvas::SetCanvasPosition(sf::Vector2f const &pos)
{
	m_sheet->SetSheetPosition(pos);
}

std::shared_ptr<CSheet> CCanvas::GetSheet()
{
	return m_sheet;
}

//------------------------ CSHEET -----------------------------

std::shared_ptr<CSheet> CSheet::Create(sf::FloatRect const& frame)
{
	return std::shared_ptr<CSheet>(new CSheet(frame));
}

void CSheet::SetSheetSize(sf::Vector2f const & size)
{
	m_background.setSize(size);
}

void CSheet::SetSheetPosition(sf::Vector2f const & pos)
{
	m_background.setPosition(pos);
}

void CSheet::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_background, states);
}

CSheet::CSheet(sf::FloatRect const& frame)
{
	SetSheetSize(sf::Vector2f(frame.width, frame.height));
	SetSheetPosition(sf::Vector2f(frame.left, frame.top));
	m_background.setFillColor(sf::Color::White);
}

}