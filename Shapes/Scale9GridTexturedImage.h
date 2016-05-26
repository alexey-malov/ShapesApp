#pragma once
#include <SFML/Graphics.hpp>
#include "TexturedImage.h"

class CScale9GridTexturedImage : public IImage
{
public:
	CScale9GridTexturedImage(std::shared_ptr<sf::Texture> const& texture, sf::IntRect const& middle);
	CScale9GridTexturedImage() = delete;
/*
	void SetTexture(std::shared_ptr<sf::Texture> const& texturePtr, bool resetRect = true);
	void SetScaleRect(sf::IntRect const& middle);*/
	void SetSize(float x, float y) override;
	sf::Vector2f GetSize() const override;
	~CScale9GridTexturedImage();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	std::vector<CTexturedImage> CreateSpritesGrid();
	bool IsImageIncludeScaleRect();
	std::shared_ptr<sf::Texture> m_texture;
	sf::IntRect m_middle;
	std::vector<CTexturedImage> m_texturedImages;
};

