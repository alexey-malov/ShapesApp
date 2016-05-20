#pragma once


class IImage : public sf::Drawable
{
public:
	virtual void SetSize(float x, float y) = 0;
	//virtual void SetPosition(float x, float y) = 0;
	virtual sf::Vector2f GetSize() const = 0;
//	virtual const sf::Vector2f GetPosition() const = 0;
//	virtual sf::FloatRect GetGlobalBounds() const = 0;
//	virtual void SetTexture(std::shared_ptr<sf::Texture> const& texturePtr, bool resetRect = false) = 0;
	virtual ~IImage() = default;
};

class IImage2 : public sf::Drawable
{
public:
	virtual void SetSize(const sf::Vector2f & size) = 0;
	virtual sf::Vector2f GetSize()const = 0;
};