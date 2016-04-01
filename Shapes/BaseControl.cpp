#include "stdafx.h"
#include "BaseControl.h"

using namespace sf;
using namespace std;

namespace ui
{

bool CBaseControl::OnEvent(sf::Event const & event)
{
	auto HandledEvent = [&](auto & child) {
		return child->OnEvent(event);
	};

	return any_of(m_children.rbegin(), m_children.rend(), HandledEvent)
		|| DispatchOwnEvent(event);
}

void CBaseControl::InsertChild(const CBaseControlPtr & control, unsigned index)
{
	if (index < m_children.size())
	{
		m_children.insert(m_children.begin() + index, control);
	}
	else
	{
		m_children.push_back(control);
	}
}

void CBaseControl::OnDraw(sf::RenderTarget & /*target*/, sf::RenderStates /*states*/) const
{
}

void CBaseControl::draw(RenderTarget & target, RenderStates states) const
{
	OnDraw(target, states);

	for (auto & child : m_children)
	{
		child->draw(target, states);
	}
}

bool CBaseControl::DispatchOwnEvent(sf::Event const & event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		return OnMousePressed(event.mouseButton);
	case sf::Event::MouseButtonReleased:
		return OnMouseReleased(event.mouseButton);
	default:
		return false;
	}
}

bool CBaseControl::OnMousePressed(sf::Event::MouseButtonEvent const &)
{
	return false;
}

bool CBaseControl::OnMouseReleased(sf::Event::MouseButtonEvent const &)
{
	return false;
}

sf::FloatRect CBaseControl::GetBoundingRect() const
{
	return sf::FloatRect();
}

}