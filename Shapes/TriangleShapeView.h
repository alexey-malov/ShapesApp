#pragma once
#include "ShapeView.h"

class CTriangleShapeView : public CShapeView
{
public:
	CTriangleShapeView(sf::Vector2f const& size, sf::Vector2f const& pos);
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) override;
	void SetSize(const sf::Vector2f & size) override;
	void SetPosition(const sf::Vector2f & position) override;
private:
	void InitTriangle(sf::Vector2f position, sf::Vector2f size);
private:
	sf::ConvexShape m_triangle;
};

