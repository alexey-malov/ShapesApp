#pragma once
#include "ShapeView.h"

class CRectangleShapeView : public CShapeView
{
public:
	CRectangleShapeView(sf::Vector2f const& size, sf::Vector2f const& pos);
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) override;
	void SetSize(const sf::Vector2f & size) override;
	void SetPosition(const sf::Vector2f & position) override;
private:
	void InitRectangle(sf::Vector2f size, sf::Vector2f position);
private:
	sf::RectangleShape m_rectangle;
};

