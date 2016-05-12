#include "stdafx.h"
#include "Ellipse.h"


ui::CEllipse::CEllipse()
{
}

float ui::CEllipse::GetRadius()
{
	return m_radius;
}

void ui::CEllipse::SetRadius(float const & radius)
{
	m_radius = radius;
}

