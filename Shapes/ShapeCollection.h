#pragma once
#include "ShapesModel.h"

namespace ui
{

class CShapeCollection
{
public:
	void AddShapeWithIndex(std::shared_ptr<IShape> & shape, size_t const& index);
	std::shared_ptr<IShape> GetShapeByIndex(size_t const& index);
private:
	std::map<size_t, std::shared_ptr<IShape>> m_shapes;
};

}
