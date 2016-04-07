#include "stdafx.h"
#include "ToolBar.h"

namespace ui
{
	std::shared_ptr<CToolBar> CToolBar::Create(sf::Vector2u const& size)
	{
		return std::shared_ptr<CToolBar>(new CToolBar(size));

	}

	CToolBar::CToolBar(sf::Vector2u const& size)
	{
		m_background.setSize({ float(size.x) ,  float(size.y * 0.15) });
		m_background.setFillColor(sf::Color(64, 64, 64, 255));


	}

	void CToolBar::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(m_background, states);
	}

	void CToolBar::AddChildWithIndex(const CBaseControlPtr & control, unsigned index)
	{
		InsertChildAtIndex(control, index);
		//set children positions
		
	}

}