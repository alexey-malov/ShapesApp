#pragma once
#include "ShapeView.h"


namespace ui
{

class CTriangleShapeView : public CShapeView
{
public:
	CTriangleShapeView(sf::FloatRect const & frame);
	void OnFrameChanged(const sf::FloatRect & newFrame) override;
	bool HitTest(sf::Vector2f const & local) const override;
protected:
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	void InitTriangle();
private:
	sf::ConvexShape m_triangle;
	sf::FloatRect m_frame;
};

}

