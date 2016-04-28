#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Image.h"

class CTexturedImage : public IImage
{
public:
	void SetTexture(std::shared_ptr<sf::Texture> const& texturePtr, bool resetRect = true) override;
	const sf::Texture* GetTexture() const;
	void SetTextureRect(const sf::IntRect& rectangle);
	const sf::IntRect& GetTextureRect() const;
	void SetPosition(float x, float y) override;
	const sf::Vector2f GetPosition() const override;
	sf::FloatRect GetGlobalBounds() const;
	void SetScale(float factorX, float factorY);
	void SetSize(float x, float y) override;
	sf::Vector2f GetSize()const override;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	sf::Sprite m_sprite;
	std::shared_ptr<sf::Texture> m_texturePtr;
};

