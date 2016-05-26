#include "stdafx.h"
#include "ShapesModel.h"

using namespace model;

model::CAbstractShape::CAbstractShape()
	: m_frame(Frame(0, 0, Pointf(0, 0)))
{
}

Frame model::CAbstractShape::GetFrame()
{
	return m_frame;
}

void model::CAbstractShape::SetFrame(Frame const& frame)
{
	m_frame = frame;
}
