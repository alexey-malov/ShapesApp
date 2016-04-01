#include "stdafx.h"
#include "Button.h"

using namespace sf;

namespace ui
{

	CButton::CButton(std::string const& name, sf::Vector2f const& pos)
		: m_background({ 100, 30 }),
		m_buttonPos(pos),
		m_buttonName(name)
{
	m_background.setPosition(m_buttonPos);
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
		std::cout << m_buttonName << std::endl;
		return true;
	}
	return false;
}

}