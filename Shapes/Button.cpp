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

void CButton::SetIcon(const std::shared_ptr<sf::Texture> & texture)
{
	m_iconTexture = texture;
	if (texture)
	{
		m_iconSprite.setTexture(*texture);
		m_iconSprite.setPosition(m_background->GetPosition()
			+ m_background->GetSize() * 0.5f
			- sf::Vector2f(m_iconSprite.getGlobalBounds().width, m_iconSprite.getGlobalBounds().height) * 0.5f);
	}
}

void CButton::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*m_background, states);
	if (m_iconTexture)
	{
		target.draw(m_iconSprite, states);
	}
}

Connection CButton::DoOnClick(OnClick::slot_type const & handler)
{
	return m_onClick.connect(handler);
}

void CButton::SetBackground(const std::shared_ptr<IImage> & image)
{
	m_background = image;
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

void CButton::OnFrameChanged(const sf::FloatRect & newRect)
{
	m_background->SetPosition(newRect.left, newRect.top);
	m_background->SetSize(newRect.width, newRect.height);
}

}