#include "stdafx.h"
#include "Triangle.h"


ui::CTriangle::CTriangle()
{
}

ui::TrianglePicks ui::CTriangle::GetPicks()
{
	return m_picks;
}

void ui::CTriangle::SetPicks(Point const & point1, Point const & point2, Point const & point3)
{
	m_picks.firstPick = point1;
	m_picks.secondPick = point2;
	m_picks.thirdPick = point3;
}
