#pragma once
#include "ShapeView.h"

namespace ui
{

class CRectangleShapeView : public CShapeView
{
public:
	CRectangleShapeView(sf::FloatRect const & frame);
	void OnFrameChanged(const sf::FloatRect & newFrame) override;
protected:
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	void InitRectangle();
private:
	sf::RectangleShape m_rectangle;
};

}

