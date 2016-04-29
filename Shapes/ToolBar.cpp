#include "stdafx.h"
#include "ToolBar.h"
#include <iostream>
namespace ui
{
static const sf::Vector2f BUTTON_SIZE = { 80.f, 80.f };

std::shared_ptr<CToolBar> CToolBar::Create(sf::Vector2u const& size)
{
	return std::shared_ptr<CToolBar>(new CToolBar(size));

}

CToolBar::CToolBar(sf::Vector2u const& size)
	: m_countChild(0)
{
	m_background.setSize({ float(size.x) ,  float(size.y * 0.15) });
	m_background.setFillColor(sf::Color(64, 64, 64, 255));


}

void CToolBar::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_background, states);
}

void CToolBar::AddChildWithIndex(unsigned index)
{
	auto button = CButton::Create();

	InsertChildAtIndex(button, index);

	m_buttons.insert({ index, CToolbarButton::Create(button) });
	std::shared_ptr<sf::Texture> backgroundTexture = std::make_shared<sf::Texture>();
	backgroundTexture->loadFromFile("./images/btn1-normal.png");
	auto textureSize = backgroundTexture->getSize();
	std::shared_ptr<IImage> image = std::make_shared<CScale9GridTexturedImage>(backgroundTexture, sf::IntRect(2, 2, 6, 6));
	button->SetBackground(image);
	button->SetFrame({ float((GetChildCount() - 1) * 50 + 5), 5, BUTTON_SIZE.x , BUTTON_SIZE.y });
}

std::shared_ptr<CToolbarButton> CToolBar::GetButton(unsigned const & index)
{
	return m_buttons.find(index)->second;
}

void CToolBar::SetButtonsBackgrounds(const std::shared_ptr<IImage> & image)
{
	for (auto &it : m_buttons)
	{
		it.second->SetBackground(image);
	}
}

sf::Vector2f CToolBar::GetToolbarSize()const
{
	return m_background.getSize();
}

void CToolBar::SetToolbarSize(sf::Vector2f const & size)
{
	m_background.setSize(size);
}

void CToolBar::SetRightIndentSize(float width)
{
	m_rightIndentSize = width;
}

float CToolBar::GetRightIndentSize() const
{
	return m_rightIndentSize;
}

}