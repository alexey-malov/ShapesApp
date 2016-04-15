#include "stdafx.h"
#include "ToolBar.h"
#include <iostream>
namespace ui
{
static const sf::Vector2f BUTTON_SIZE = { 50.0f, 20.0f };

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

	button->SetFrame({ float((GetChildCount() - 1) * 50 + 5), 5, BUTTON_SIZE.x , BUTTON_SIZE.y });
}

std::shared_ptr<CToolbarButton> CToolBar::GetButton(unsigned const & index)
{
	return m_buttons.find(index)->second;
}

void CToolBar::SetButtonsBackgrounds(const std::shared_ptr<sf::Texture>& texture)
{
	for (auto &it : m_buttons)
	{
		it.second->SetBackground(texture);
	}
}

}