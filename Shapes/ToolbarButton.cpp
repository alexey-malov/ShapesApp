#include "stdafx.h"
#include "ToolbarButton.h"

namespace ui
{
CToolbarButton::CToolbarButton(std::shared_ptr<CButton> & button)
{
	m_button = button;
}

std::shared_ptr<CToolbarButton> CToolbarButton::Create(std::shared_ptr<CButton> & button)
{
	return std::shared_ptr<CToolbarButton>(new CToolbarButton(button));
}

void CToolbarButton::SetAction(OnClick::slot_type const & handler)
{
	m_connection = m_button->DoOnClick(handler);
}

void CToolbarButton::SetIcon(const std::shared_ptr<sf::Texture>& texture)
{
	m_button->SetIcon(texture);
}

void CToolbarButton::SetBackground(const std::shared_ptr<sf::Texture>& texture)
{
	m_button->SetBackground(texture);
}

}