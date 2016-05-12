#include "stdafx.h"
#include "ShapeCollection.h"

void ui::CShapeCollection::AddShapeWithIndex(std::shared_ptr<ui::IShape> & shape, size_t const & index)
{
	m_shapes.insert({ index, shape });
}

std::shared_ptr<ui::IShape> ui::CShapeCollection::GetShapeByIndex(size_t const& index)
{
	return m_shapes.find(index)->second;
}
