#pragma once
#include <SFML/Graphics.hpp>

class IBackground : public sf::Drawable
{
public:
	virtual void SetSize(float x, float y) = 0;
	virtual sf::Vector2f GetSize() const = 0;
	virtual sf::FloatRect GetGlobalBounds() const = 0;
	virtual void SetSize(sf::Vector2f const& size) = 0;
};