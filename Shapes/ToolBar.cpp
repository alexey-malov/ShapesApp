#include "stdafx.h"
#include "ToolBar.h"
#include <iostream>
namespace ui
{
	static const sf::Vector2f BUTTON_SIZE = { 50.0f, 20.0f };

	std::shared_ptr<CToolBar> CToolBar::Create(sf::Vector2u const& size)
	{
		return std::shared_ptr<CToolBar>(new CToolBar(size));

	}

	CToolBar::CToolBar(sf::Vector2u const& size)
		: m_countChild(0)
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

		control->SetFrame({ float(GetChildCount() * 50 + 5), 5, BUTTON_SIZE.x , BUTTON_SIZE.y });

		InsertChildAtIndex(control, index);

	}

	void CToolBar::SetRightIndentSize(float width)
	{
		m_rightIndentSize = width;
	}

	bool CToolBar::OnWindowResized(sf::Event::SizeEvent const& event)
	{
		if (event.width != m_background.getSize().x)
		{
			m_background.setSize({ static_cast<float>(event.width) - m_rightIndentSize
				, m_background.getSize().y });
			return true;
		}
		return false;
	}

}