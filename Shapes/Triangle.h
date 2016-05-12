#pragma once
#include "ShapesModel.h"

namespace ui
{

struct Point
{
	Point()
		: x(0)
		, y(0)
	{
	}
	float x;
	float y;
};

struct TrianglePicks
{
	Point firstPick;
	Point secondPick;
	Point thirdPick;
};

class CTriangle :
	public CAbstractShape
{
public:
	CTriangle();

	TrianglePicks GetPicks();
	void SetPicks(Point const& point1, Point const& point2, Point const& point3);

private:
	TrianglePicks m_picks;
};

}

