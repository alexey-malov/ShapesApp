#pragma once
#include <SFML/Graphics.hpp>
#include "TexturedImage.h"

enum NinePatchCorners
{
	UPPER_LEFT,
	UPPER_RIGHT,
	BOTTOM_RIHGT,
	BOTTOM_LEFT
};

class CScale9GridTexturedImage : public IBackground
{
public:
	CScale9GridTexturedImage(std::shared_ptr<sf::Texture> const& texture, sf::IntRect const& middle);
	CScale9GridTexturedImage();
	void SetTexture(std::shared_ptr<sf::Texture> const& texturePtr, bool resetScaleRect = true);
	void SetScaleRect(sf::IntRect const& middle);
	void SetSize(float x, float y) override;
	void SetSize(sf::Vector2f const& size) override;
	sf::Vector2f GetSize() const;
	sf::FloatRect GetGlobalBounds() const;
	~CScale9GridTexturedImage();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	std::vector<CTexturedImage> CreateSpritesGrid();
	void UpdateCellsPosition();
	bool IsImageIncludeScaleRect();
	std::shared_ptr<sf::Texture> m_texture;
	sf::IntRect m_middle;
	std::vector<CTexturedImage> m_texturedImages;
};

