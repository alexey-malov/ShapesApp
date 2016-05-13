#pragma once
#include "ShapesModel.h"

namespace ui
{
class CRectangle :
	public CAbstractShape
{
public:
	CRectangle();
	
	Pointf GetSize();
	void SetSize(Pointf const& size);

private:
	Pointf m_size;
};

}