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
	: m_background({ 100, 30 })
{
}

void CButton::SetIcon(std::shared_ptr<sf::Texture> texture)
{
	m_image.setTexture(*texture);
	m_image.setPosition(m_background.getPosition()
		+ m_background.getSize() * 0.5f
		- sf::Vector2f(m_image.getGlobalBounds().width, m_image.getGlobalBounds().height) * 0.5f);
}

void CButton::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_background, states);
	target.draw(m_image, states);
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