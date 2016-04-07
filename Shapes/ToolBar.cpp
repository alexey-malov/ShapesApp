#include "stdafx.h"
#include "ToolBar.h"

namespace ui
{
	CToolBar::CToolBar(sf::RenderWindow & window)
	{
		m_background.setSize({ float(window.getSize().x),  float(window.getSize().y * 0.15) });
		m_background.setFillColor(sf::Color(64, 64, 64, 255));


	}

	void CToolBar::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(m_background, states);
	}
}