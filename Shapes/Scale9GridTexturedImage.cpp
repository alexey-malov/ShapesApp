#include "stdafx.h"
#include "Scale9GridTexturedImage.h"



CScale9GridTexturedImage::CScale9GridTexturedImage(std::shared_ptr<sf::Texture> const& texturePtr, sf::IntRect const& scaleRectSize)
	:m_texture(texturePtr)
	, m_middle(scaleRectSize)
{
	assert(texturePtr);
	if (!IsImageIncludeScaleRect())
	{
		throw std::invalid_argument("Image must include scale rect");
	}
	m_texturedImages = CreateSpritesGrid();
	UpdateCellsPosition();
}

CScale9GridTexturedImage::CScale9GridTexturedImage()
{

}

void CScale9GridTexturedImage::SetTexture(std::shared_ptr<sf::Texture> const & texturePtr, bool resetScaleRect)
{
	assert(texturePtr);
	m_texture = texturePtr;
	auto textureSize = m_texture->getSize();
	if (resetScaleRect)
	{
		m_middle = sf::IntRect(0, 0, textureSize.x, textureSize.y);
	}
	m_texturedImages = CreateSpritesGrid();
	UpdateCellsPosition();
}

void CScale9GridTexturedImage::SetScaleRect(sf::IntRect const & middle)
{
	if (!IsImageIncludeScaleRect())
	{
		throw std::invalid_argument("Image must include scale rect");
	}
	m_middle = middle;
	m_texturedImages = CreateSpritesGrid();
	UpdateCellsPosition();
}

void CScale9GridTexturedImage::SetSize(float x, float y)
{
	auto startPos = GetPosition();
	auto textureSize = m_texture->getSize();
	auto scaleRectX = x - textureSize.x;
	auto scaleRectY = y - textureSize.y;
	/*if (scaleRectX < 0) { scaleRectX = 0; }
	if (scaleRectY < 0) { scaleRectY = 0; }*/
	m_texturedImages[8].SetSize(m_texturedImages[8].GetSize().x  + scaleRectX,
		m_texturedImages[8].GetSize().y + scaleRectY);
	m_texturedImages[1].SetSize(m_texturedImages[1].GetSize().x + scaleRectX,
		m_texturedImages[1].GetSize().y);
	m_texturedImages[3].SetSize(m_texturedImages[3].GetSize().x,
		m_texturedImages[3].GetSize().y + scaleRectY);
	m_texturedImages[5].SetSize(m_texturedImages[5].GetSize().x + scaleRectX,
		m_texturedImages[5].GetSize().y);
	m_texturedImages[7].SetSize(m_texturedImages[7].GetSize().x,
		m_texturedImages[7].GetSize().y + scaleRectY);
	UpdateCellsPosition();
	SetPosition(startPos.x, startPos.y);
}

sf::Vector2f CScale9GridTexturedImage::GetSize() const
{
	auto height = m_texturedImages[0].GetSize().y + m_texturedImages[6].GetSize().y + m_texturedImages[7].GetSize().y;
	auto width = m_texturedImages[0].GetSize().x + m_texturedImages[1].GetSize().x + m_texturedImages[2].GetSize().x;
	return sf::Vector2f(width, height);
}

sf::FloatRect CScale9GridTexturedImage::GetGlobalBounds() const
{
	auto pos = sf::Vector2f(m_texturedImages[0].GetPosition());
	return sf::FloatRect(pos.x, pos.y, GetSize().x, GetSize().y);
}

void CScale9GridTexturedImage::SetPosition(float x, float y)
{
	m_texturedImages[8].SetPosition(x + m_texturedImages[0].GetSize().x,
		y + m_texturedImages[0].GetSize().y);
	UpdateCellsPosition();
}

const sf::Vector2f CScale9GridTexturedImage::GetPosition() const
{
	return m_texturedImages[8].GetPosition() - m_texturedImages[0].GetSize() - m_texturedImages[8].GetSize() / 2.f;
}

CScale9GridTexturedImage::~CScale9GridTexturedImage()
{
}

void CScale9GridTexturedImage::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto & image : m_texturedImages)
	{
		target.draw(image, states);
	}
}

std::vector<CTexturedImage> CScale9GridTexturedImage::CreateSpritesGrid()
{
	assert(m_texture);
	std::vector<CTexturedImage> sprites(9);
	for (auto & sprite : sprites)
	{
		sprite.SetTexture(m_texture);
	}
	auto middleUpperRight = m_middle.left + m_middle.width;
	auto middleBottomLeft = m_middle.top + m_middle.height;
	sprites[0].SetTextureRect(sf::IntRect(0, 0, m_middle.left, m_middle.top));
	sprites[1].SetTextureRect(sf::IntRect(m_middle.left, 0, m_middle.width, m_middle.top));
	sprites[2].SetTextureRect(sf::IntRect(
		middleUpperRight
		, 0
		, m_texture->getSize().x - middleUpperRight
		, m_middle.top));
	sprites[3].SetTextureRect(sf::IntRect(
		middleUpperRight
		, m_middle.top
		, m_texture->getSize().x - middleUpperRight
		, m_middle.height));
	sprites[4].SetTextureRect(sf::IntRect(
		middleUpperRight
		, middleBottomLeft
		, m_texture->getSize().x - middleUpperRight
		, m_texture->getSize().y - middleBottomLeft));
	sprites[5].SetTextureRect(sf::IntRect(
		m_middle.left
		, middleBottomLeft
		, m_middle.width
		, m_texture->getSize().y - middleBottomLeft));
	sprites[6].SetTextureRect(sf::IntRect(
		0
		, middleBottomLeft
		, m_middle.left
		, m_texture->getSize().y - middleBottomLeft));
	sprites[7].SetTextureRect(sf::IntRect(
		0
		, m_middle.top
		, m_middle.left
		, m_middle.height));
	sprites[8].SetTextureRect(m_middle);
	sprites[8].SetPosition(static_cast<float>(m_middle.left), static_cast<float>(m_middle.top));
	return sprites;
}

void CScale9GridTexturedImage::UpdateCellsPosition()
{
	auto middle = m_texturedImages[8].GetGlobalBounds();
	auto middleUpperRight = middle.left + middle.width;
	auto middleBottomLeft = middle.top + middle.height;
	m_texturedImages[0].SetPosition(middle.left - m_texturedImages[0].GetSize().x,
		middle.top - m_texturedImages[0].GetSize().y);
	m_texturedImages[1].SetPosition(middle.left, middle.top - m_texturedImages[1].GetSize().y);
	m_texturedImages[2].SetPosition(middleUpperRight, middle.top - m_texturedImages[2].GetSize().y);
	m_texturedImages[3].SetPosition(middleUpperRight, middle.top);
	m_texturedImages[4].SetPosition(middleUpperRight, middleBottomLeft);
	m_texturedImages[5].SetPosition(middle.left, middleBottomLeft);
	m_texturedImages[6].SetPosition(middle.left - m_texturedImages[6].GetSize().x, middleBottomLeft);
	m_texturedImages[7].SetPosition(middle.left - m_texturedImages[7].GetSize().x, middle.top);
}

bool CScale9GridTexturedImage::IsImageIncludeScaleRect()
{
	if (static_cast<unsigned>(m_middle.left + m_middle.width) <= m_texture->getSize().x
	&& static_cast<unsigned>(m_middle.top + m_middle.height) <= m_texture->getSize().y)
	{
		return true;
	}
	return false;
}
