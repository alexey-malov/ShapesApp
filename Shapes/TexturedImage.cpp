#include "stdafx.h"
#include "TexturedImage.h"

void CTexturedImage::SetTexture(std::shared_ptr<sf::Texture> const & texturePtr, bool resetRect)
{
	m_texturePtr = texturePtr;
	m_sprite.setTexture(*m_texturePtr, resetRect);
}
const sf::Texture * CTexturedImage::GetTexture() const
{
	return m_sprite.getTexture();
}
void CTexturedImage::SetTextureRect(const sf::IntRect & rectangle)
{
	m_sprite.setTextureRect(rectangle);
}
const sf::IntRect & CTexturedImage::GetTextureRect() const
{
	return m_sprite.getTextureRect();
}
void CTexturedImage::SetPosition(float x, float y)
{
	m_sprite.setPosition(x, y);
}
void CTexturedImage::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

const sf::Vector2f CTexturedImage::GetPosition() const
{
	return m_sprite.getPosition();
}

sf::FloatRect CTexturedImage::GetGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

void CTexturedImage::SetScale(float factorX, float factorY)
{
	m_sprite.setScale(factorX, factorY);
}


void CTexturedImage::SetSize(float x, float y)
{
	if (GetSize().y == 0)
	{
		m_sprite.setScale(x / GetSize().x, 1);
	}
	else if (GetSize().x == 0)
	{
		m_sprite.setScale(1, y / GetSize().y);
	}
	else
	{
		m_sprite.setScale(x / GetSize().x, y / GetSize().y);
	}
}

sf::Vector2f CTexturedImage::GetSize() const
{
	auto bounds = m_sprite.getGlobalBounds();
	return sf::Vector2f(bounds.width, bounds.height);
}

CTexturedImage2::CTexturedImage2(const std::shared_ptr<sf::Texture>& texture)
	:m_texture(texture)
{
}

void CTexturedImage2::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::Sprite spr;
	spr.setTexture(*m_texture);
	sf::Transform t;
	auto originalSize = m_texture->getSize();
	t.scale(sf::Vector2f(m_size.x / originalSize.x, m_size.y / originalSize.y));
	states.transform.combine(t);

	target.draw(spr, states);
}

void CTexturedImage2::SetSize(const sf::Vector2f & size)
{
	m_size = size;
}

sf::Vector2f CTexturedImage2::GetSize() const
{
	return m_size;
}
