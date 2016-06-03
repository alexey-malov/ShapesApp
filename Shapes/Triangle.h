#pragma once
#include "ShapesModel.h"

namespace model
{


struct TrianglePicks
{
	Pointf firstPick;
	Pointf secondPick;
	Pointf thirdPick;
};

class CTriangle :
	public CAbstractShape
{
public:
	CTriangle();

	void SetFrame(Frame const& frame) override;
	TrianglePicks GetPicks();
	void SetPicks();

private:
	TrianglePicks m_picks;
};

}

