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
	if (IsContainButton({ float(event.x), float(event.y) }))
	{
		ChangeColor(ButtonState::PRESSED);
		isPressed = true;
		m_onClick();
		return true;
	}
	return false;
}

bool CButton::OnMouseReleased(sf::Event::MouseButtonEvent const& event)
{
	isPressed = false;
	if (IsContainButton({ float(event.x), float(event.y) }))
	{
		ChangeColor(ButtonState::HOVERED);
		return true;
	}
	return false;
}

bool CButton::OnMouseMoved(sf::Event::MouseMoveEvent const& event)
{
	if (IsContainButton({ float(event.x), float(event.y) })) 
	{
		if (!isPressed)
		{
			ChangeColor(ButtonState::HOVERED);
		}
		return true;
	}
	isPressed = false;
	ChangeColor(ButtonState::NORMAL);
	return false;
}

void CButton::ChangeColor(const ButtonState & state)
{
	switch (state)
	{
	case ButtonState::NORMAL:
		m_background.setFillColor(sf::Color::White);
		break;
	case ButtonState::HOVERED:
		m_background.setFillColor(sf::Color::Yellow);
		break;
	case ButtonState::PRESSED:
		m_background.setFillColor(sf::Color::Blue);
		break;
	}
}

bool CButton::IsContainButton(sf::Vector2f const & pos)
{
	return m_background.getGlobalBounds().contains(pos);
}

}