#pragma once
#include "ShapeView.h"

namespace ui
{

class CEllipseShapeView : public CShapeView
{
public:
	CEllipseShapeView(sf::FloatRect const & frame);
	void OnFrameChanged(const sf::FloatRect & newFrame) override;
	bool HitTest(sf::Vector2f const & local) const override;
protected:
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	void InitCircle();
private:
	sf::CircleShape m_circle;
};

}