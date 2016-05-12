#include "stdafx.h"
#include "RectangleModel.h"

ui::CRectangle::CRectangle()
	: m_size({0, 0})
{
}

ui::Pointf ui::CRectangle::GetSize()
{
	return m_size;
}

void ui::CRectangle::SetSize(Pointf const & size)
{
	m_size = size;
}
