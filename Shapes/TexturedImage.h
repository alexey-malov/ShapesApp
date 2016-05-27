#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Image.h"

class CTexturedImage : public IImage
{
public:
	CTexturedImage(const std::shared_ptr<sf::Texture> & texture);

	void SetTextureRect(const sf::IntRect& rectangle);

	void SetSize(float x, float y) override;
	sf::Vector2f GetSize()const override;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;

	std::shared_ptr<sf::Texture> m_texturePtr;
	sf::Sprite m_sprite;
	sf::Vector2f m_size;
};