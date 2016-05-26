#include "stdafx.h"
#include "Button.h"
#include "Image.h"
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

void CButton::SetIcon(const std::shared_ptr<sf::Texture> & texture)
{
	m_iconTexture = texture;
	if (texture)
	{
		m_iconSprite.setTexture(*texture);
		m_iconSprite.setPosition(m_background.getPosition()
			+ m_background.getSize() * 0.5f
			- sf::Vector2f(m_iconSprite.getGlobalBounds().width, m_iconSprite.getGlobalBounds().height) * 0.5f);
	}
}

void CButton::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*m_backgroundTexture, states);
	if (m_iconTexture)
	{
		target.draw(m_iconSprite, states);
	}
}

Connection CButton::DoOnClick(OnClick::slot_type const & handler)
{
	return m_onClick.connect(handler);
}

void CButton::SetBackground(const std::shared_ptr<IImage> & texture)
{
	m_backgroundTexture = texture;
	//m_background.setTexture(m_backgroundTexture.get());
}

bool CButton::OnMousePressed(sf::Event::MouseButtonEvent const & event)
{
	if (MouseHitTest({ event.x, event.y }))
	{
		ChangeColor(ButtonState::PRESSED);
		m_isPressed = true;
		m_onClick();
		return true;
	}
	return false;
}

void CButton::OnFrameChanged(const sf::FloatRect & newRect)
{
	m_background.setSize({ newRect.width, newRect.height });
}

bool CButton::OnMouseReleased(sf::Event::MouseButtonEvent const& event)
{
	m_isPressed = false;
	if (MouseHitTest({ event.x, event.y }))
	{
		ChangeColor(ButtonState::HOVERED);
		return true;
	}
	return false;
}

void CButton::OnMouseOver(sf::Event::MouseMoveEvent const& event)
{
	if (MouseHitTest({ event.x, event.y }))
	{
		if (!m_isPressed)
		{
			ChangeColor(ButtonState::HOVERED);
			m_isPressed = false;
		}
	}
}

void CButton::OnMouseLeave(sf::Event::MouseMoveEvent const& event)
{
	if (!MouseHitTest({ event.x, event.y }))
	{
		ChangeColor(ButtonState::NORMAL);
		m_isPressed = false;
	}
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

bool CButton::MouseHitTest(const sf::Vector2i & mousePos) const
{
	return HitTest(GlobalToLocal(Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))));
}

}