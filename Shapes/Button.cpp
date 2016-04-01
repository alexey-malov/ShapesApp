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

Connection CButton::DoOnClick(OnClick::slot_type const &handler)
{
	return m_onClick.connect(handler);
}

bool CButton::OnMousePressed(sf::Event::MouseButtonEvent const & event)
{
	sf::Vector2f pt(float(event.x), float(event.y));
	if (m_background.getGlobalBounds().contains(pt))
	{
		m_onClick();
		return true;
	}
	return false;
}

}