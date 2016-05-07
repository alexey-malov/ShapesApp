#pragma once
#include "ShapeView.h"

class CEllipseShapeView : public CShapeView
{
public:
	CEllipseShapeView(sf::Vector2f const& size, sf::Vector2f const& pos);
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) override;
	void SetSize(const sf::Vector2f & size) override;
	void SetPosition(const sf::Vector2f & position) override;
private:
	void InitCircle(sf::Vector2f position, sf::Vector2f size);
private:
	sf::CircleShape m_circle;
};

