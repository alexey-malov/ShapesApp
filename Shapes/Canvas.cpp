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
	auto oldRect = shape->GetFrame();
	auto sheetRect = m_sheet->GetFrame();
	shape->SetFrame({ oldRect.left + sheetRect.left * 0.5f, oldRect.top + sheetRect.top * 0.5f,
						oldRect.width, oldRect.height });
}

std::shared_ptr<CShapeView> CCanvas::GetShape(unsigned index)
{
	assert(index >= m_shapes.size());
	return m_shapes[index];
}

void CCanvas::SetFrame(sf::FloatRect const & newFrame)
{
	m_sheet->SetFrame(newFrame);
}

CCanvas::CCanvas(sf::FloatRect const& frame)
	: m_sheet(ui::CSheet::Create(frame))
{
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

void CSheet::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_background, states);
}

void CSheet::OnFrameChanged(const sf::FloatRect & newFrame)
{
	m_background.setPosition(sf::Vector2f(newFrame.left, newFrame.top));
	m_background.setSize(sf::Vector2f(newFrame.width, newFrame.height));
}

CSheet::CSheet(sf::FloatRect const& frame)
{
	SetFrame(frame);
	m_background.setFillColor(sf::Color::White);
}

}