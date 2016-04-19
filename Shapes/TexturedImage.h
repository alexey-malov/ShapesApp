#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Background.h"

class CTexturedImage : public IBackground
{
public:
	void SetTexture(std::shared_ptr<sf::Texture> const& texturePtr, bool resetRect = false);
	const sf::Texture* GetTexture() const;
	void SetTextureRect(const sf::IntRect& rectangle);
	const sf::IntRect& GetTextureRect() const;
	void SetPosition(float x, float y);
	const sf::Vector2f GetPosition() const;
	sf::FloatRect GetGlobalBounds() const;
	void SetScale(float factorX, float factorY);
	void SetSize(float x, float y) override;
	void SetSize(sf::Vector2f const& size) override;
	sf::Vector2f GetSize()const override;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
	sf::Sprite m_sprite;
	std::shared_ptr<sf::Texture> m_texturePtr;
};

