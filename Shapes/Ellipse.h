#pragma once
#include "ShapesModel.h"

namespace ui
{

class CEllipse :
	public CAbstractShape
{
public:
	CEllipse();
	
	float GetRadius();
	void SetRadius(float const& radius);

private:
	float m_radius;
};

}