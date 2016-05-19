#pragma once
#include "ShapeView.h"
#include "BaseControl.h"

namespace ui
{

class CCanvas : public CBaseControl
{
public:
	static std::shared_ptr<CCanvas> Create(sf::Vector2u const& size);


	void Insert(std::shared_ptr<CShapeView> const & shape, unsigned index);
	std::shared_ptr<CShapeView> GetShape(unsigned index);

	sf::Vector2f GetCanvasSize()const;
	void SetCanvasSize(sf::Vector2f const &size);

	sf::Vector2f GetCanvasPosition()const;
	void SetCanvasPosition(sf::Vector2f const &pos);

protected:
	void OnDraw(sf::RenderTarget & target, sf::RenderStates states) const override;
private:
	CCanvas(sf::Vector2u const& size);
	CBaseControlPtr m_canvas;
	sf::RectangleShape m_background;

	std::vector<std::shared_ptr<CShapeView>> m_shapes;
};

}