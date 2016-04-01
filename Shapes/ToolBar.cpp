#include "stdafx.h"
#include "ToolBar.h"

namespace ui
{
	CToolBar::CToolBar(sf::RenderWindow & window)
		: m_targetWindow(window)
	{
		m_background.setSize({ float(m_targetWindow.getSize().x),  float(m_targetWindow.getSize().y * 0.15) });
		m_background.setFillColor(sf::Color(64, 64, 64, 255));

		InsertChild(std::make_shared<ui::CButton>(CButton("Circle", { 0, 0 })));
		InsertChild(std::make_shared<ui::CButton>(CButton("Rectangle", {101, 0})));
		InsertChild(std::make_shared<ui::CButton>(CButton("Triangle", {202, 0})));


	}


	void CToolBar::InsertChild(const CButtonPtr & control)
	{
		m_background.setSize({ float(m_targetWindow.getSize().x),  float(m_targetWindow.getSize().y * 0.15) });

		m_children.push_back(control);
	}

	void CToolBar::OnEvent(sf::Event const& event)
	{
		for (auto & child : m_children)
		{
			child->OnEvent(event);
		}
	}


	void CToolBar::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		target.draw(m_background, states);
	}

	void CToolBar::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		OnDraw(target, states);

		for (auto & child : m_children)
		{
			target.draw(*child, states);
		}
	}
}