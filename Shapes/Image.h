#pragma once


class IImage : public sf::Drawable
{
public:
	virtual void SetSize(float x, float y) = 0;
	virtual sf::Vector2f GetSize() const = 0;
};