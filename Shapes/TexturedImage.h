#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Image.h"

class CTexturedImage : public IImage
{
public:
	CTexturedImage(const std::shared_ptr<sf::Texture> & texture);
/*
	void SetTexture(std::shared_ptr<sf::Texture> const& texturePtr, bool resetRect = true);
	const sf::Texture* GetTexture() const;
	void SetTextureRect(const sf::IntRect& rectangle);*/
//	const sf::IntRect& GetTextureRect() const;
//	void SetPosition(float x, float y) override;
//	const sf::Vector2f GetPosition() const override;
//	sf::FloatRect GetGlobalBounds() const;
//	void SetScale(float factorX, float factorY);
	void SetTextureRect(const sf::IntRect& rectangle);
	void SetSize(float x, float y) override;
	sf::Vector2f GetSize()const override;
	void draw(sf::RenderTarget& target, sf::RenderStates states)const override;
private:
	std::shared_ptr<sf::Texture> m_texturePtr;
	sf::Sprite m_sprite;
	sf::Vector2f m_size;
};

class CTexturedImage2 : public IImage2
{
public:
	CTexturedImage2(const std::shared_ptr<sf::Texture> & texture);
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void SetSize(const sf::Vector2f & size) override;
	sf::Vector2f GetSize() const override;
private:
	std::shared_ptr<sf::Texture> m_texture;
	sf::Vector2f m_size;
};