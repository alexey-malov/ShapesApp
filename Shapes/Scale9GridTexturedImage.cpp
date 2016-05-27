#include "stdafx.h"
#include "Scale9GridTexturedImage.h"



CScale9GridTexturedImage::CScale9GridTexturedImage(std::shared_ptr<sf::Texture> const& texturePtr, sf::IntRect const& scaleRectSize)
	:m_texture(texturePtr)
	, m_middle(scaleRectSize)
{
	assert(texturePtr);
	if (!IsImageIncludesScaleRect())
	{
		throw std::invalid_argument("Image must include scale rect");
	}
	m_texturedImages = CreateSpritesGrid();
}

void CScale9GridTexturedImage::SetSize(float x, float y)
{
	auto textureSize = m_texture->getSize();
	auto scaleRectX = x - GetSize().x;
	auto scaleRectY = y - GetSize().y;

	m_middle.width += static_cast<int>(scaleRectX);
	m_middle.height += static_cast<int>(scaleRectY);

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

}

sf::Vector2f CScale9GridTexturedImage::GetSize() const
{
	auto height = m_texturedImages[0].GetSize().y + m_texturedImages[6].GetSize().y + m_texturedImages[7].GetSize().y;
	auto width = m_texturedImages[0].GetSize().x + m_texturedImages[1].GetSize().x + m_texturedImages[2].GetSize().x;
	return sf::Vector2f(width, height);
}

CScale9GridTexturedImage::~CScale9GridTexturedImage()
{
}

void CScale9GridTexturedImage::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	auto middleUpperRight = m_middle.left + m_middle.width;
	auto middleBottomLeft = m_middle.top + m_middle.height;
	auto tmpTransform0 = states.transform;
	auto tmpTransform1 = states.transform;
	auto tmpTransform2 = states.transform;
	auto tmpTransform3 = states.transform;
	auto tmpTransform4 = states.transform;
	auto tmpTransform5 = states.transform;
	auto tmpTransform6 = states.transform;
	auto tmpTransform7 = states.transform;
	auto tmpTransform8 = states.transform;
	target.draw(m_texturedImages[0], tmpTransform0.translate(
		m_middle.left - m_texturedImages[0].GetSize().x,
		m_middle.top - m_texturedImages[0].GetSize().y
	));
	target.draw(m_texturedImages[1], tmpTransform1.translate(
		static_cast<float>(m_middle.left), m_middle.top - m_texturedImages[1].GetSize().y
	));
	target.draw(m_texturedImages[2], tmpTransform2.translate(
		static_cast<float>(middleUpperRight), m_middle.top - m_texturedImages[2].GetSize().y
	));
	target.draw(m_texturedImages[3], tmpTransform3.translate(
		static_cast<float>(middleUpperRight), static_cast<float>(m_middle.top)
	));
	target.draw(m_texturedImages[4], tmpTransform4.translate(
		static_cast<float>(middleUpperRight), static_cast<float>(middleBottomLeft)
	));
	target.draw(m_texturedImages[5], tmpTransform5.translate(
		static_cast<float>(m_middle.left), static_cast<float>(middleBottomLeft)
	));
	target.draw(m_texturedImages[6], tmpTransform6.translate(
		m_middle.left - m_texturedImages[6].GetSize().x, static_cast<float>(middleBottomLeft)
	));
	target.draw(m_texturedImages[7], tmpTransform7.translate(
		m_middle.left - m_texturedImages[7].GetSize().x, static_cast<float>(m_middle.top)
	));
	target.draw(m_texturedImages[8], tmpTransform8.translate(
		static_cast<float>(m_middle.left), static_cast<float>(m_middle.top)
	));
}

std::vector<CTexturedImage> CScale9GridTexturedImage::CreateSpritesGrid()
{
	assert(m_texture);
	std::vector<CTexturedImage> sprites;
	for (size_t spritesCount = 0; spritesCount < 9; spritesCount++)
	{
		sprites.push_back(CTexturedImage(m_texture));
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
	return sprites;
}

bool CScale9GridTexturedImage::IsImageIncludesScaleRect()const
{
	if (static_cast<unsigned>(m_middle.left + m_middle.width) <= m_texture->getSize().x
	&& static_cast<unsigned>(m_middle.top + m_middle.height) <= m_texture->getSize().y)
	{
		return true;
	}
	return false;
}
