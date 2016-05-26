#include "stdafx.h"
#include "ShapeCollection.h"

void model::CShapeCollection::AddShapeWithIndex(std::shared_ptr<model::IShape> & shape, size_t const & index)
{
	m_shapes.insert({ index, shape });
}

std::shared_ptr<IShape> model::CShapeCollection::GetShapeByIndex(size_t const & index)
{
	return m_shapes.find(index)->second;
}

