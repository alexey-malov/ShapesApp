#include "stdafx.h"
#include "ShapesModel.h"

using namespace ui;

ui::CAbstractShape::CAbstractShape()
	: m_position({ 0, 0 })
	, m_rotation(0)
	, m_scale({ 1, 1 })
	, m_borderWidth(0)
	, m_origin(0, 0)
	, m_fillColor(SColor(0, 0, 0, 0))
	, m_borderColor(SColor(0, 0, 0, 0))
{
}

Pointf ui::CAbstractShape::GetPosition()
{
	return m_position;
}

void ui::CAbstractShape::SetPosition(Pointf const & position)
{
	m_position = position;
}

SColor ui::CAbstractShape::GetFillColor()
{
	return m_fillColor;
}

void ui::CAbstractShape::SetFillColor(SColor const & color)
{
	m_fillColor = color;
}

SColor ui::CAbstractShape::GetBorderColor()
{
	return m_borderColor;
}

void ui::CAbstractShape::SetBorderColor(SColor const & color)
{
	m_borderColor = color;
}

Pointf ui::CAbstractShape::GetScale()
{
	return m_scale;
}

void ui::CAbstractShape::SetScale(Pointf const & scale)
{
	m_scale = scale;
}

float ui::CAbstractShape::GetBorderSize()
{
	return m_borderWidth;
}

void ui::CAbstractShape::SetBorderSize(float const & borderWidth)
{
	m_borderWidth = borderWidth;
}
