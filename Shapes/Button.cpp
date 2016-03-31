#include "stdafx.h"
#include "Button.h"

using namespace sf;

namespace ui
{

	CButton::CButton()
		: m_background({ 100, 30 })
	{
	}

	void CButton::SetPosition(sf::Vector2f const & pos)
	{
		m_background.setPosition(pos);
	}

	void CButton::SetSize(sf::Vector2f const size)
	{
		m_background.setSize(size);
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
			ChangeColor(ButtonState::PRESSED);
			return true;
		}
		return false;
	}

	bool CButton::OnMouseReleased(sf::Event::MouseButtonEvent const& event)
	{
		sf::Vector2f pt(float(event.x), float(event.y));
		if (m_background.getGlobalBounds().contains(pt))
		{
			ChangeColor(ButtonState::HOVERED);
			return true;
		}
		return false;
	}

	bool CButton::OnMouseHovered(sf::Vector2f const & pos)
	{
		if (m_background.getGlobalBounds().contains(pos))
		{
			std::cout << "hovered" << std::endl;
			ChangeColor(ButtonState::HOVERED);
			return true;
		}
		ChangeColor(ButtonState::NORMAL);
		return false;		
	}

void CButton::ChangeColor(const ButtonState & state) {
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


}