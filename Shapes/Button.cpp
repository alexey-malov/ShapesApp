#include "stdafx.h"
#include "Button.h"

using namespace sf;

namespace ui
{

std::shared_ptr<CButton> CButton::Create()
{
	return std::shared_ptr<CButton>(new CButton());
}

CButton::CButton()
{
}

void CButton::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*m_background, states);
}

Connection CButton::DoOnClick(OnClick::slot_type const &handler)
{
	return m_onClick.connect(handler);
}

bool CButton::OnMousePressed(sf::Event::MouseButtonEvent const & event)
{
	sf::Vector2f pt(float(event.x), float(event.y));
	if (m_background->GetGlobalBounds().contains(pt))
	{
		m_onClick();
		return true;
	}
	return false;
}

void CButton::SetBackground(std::shared_ptr<IBackground> const& background)
{
	m_background = background;
}

}