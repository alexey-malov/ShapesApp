#include "stdafx.h"
#include "Button.h"

using namespace sf;

namespace ui
{

CButton::CButton()
	: m_background({ 100, 30 })
{
}

void CButton::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_background, states);
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
void CButton::SetBackground(const sf::Texture & texture)
{
	m_backgroundTesture = texture; // для коммита
	m_background.setTexture(&m_backgroundTesture);
}

}