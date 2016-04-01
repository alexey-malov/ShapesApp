#include "stdafx.h"
#include "Button.h"

using namespace sf;

namespace ui
{

CButton::CButton()
	: m_background({ 100, 30 })
{
}

void CButton::setIcon(sf::Texture * texture)
{
	m_image.setTexture(*texture);
	m_image.setPosition(m_background.getPosition()
		+ m_background.getSize() * 0.5f
		- sf::Vector2f(m_image.getGlobalBounds().width, m_image.getGlobalBounds().height) *0.5f);
}

void CButton::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_background, states);
	target.draw(m_image, states);
}

bool CButton::OnMousePressed(sf::Event::MouseButtonEvent const & event)
{
	sf::Vector2f pt(float(event.x), float(event.y));
	if (m_background.getGlobalBounds().contains(pt))
	{
		// TODO: action.
		return true;
	}
	return false;
}

}