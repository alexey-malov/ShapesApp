#include "stdafx.h"
#include "BaseControl.h"

using namespace sf;

namespace ui
{

bool CBaseControl::OnEvent(sf::Event const & event)
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

void CBaseControl::OnDraw(sf::RenderTarget & /*target*/, sf::RenderStates /*states*/) const
{
}

void CBaseControl::draw(RenderTarget & target, RenderStates states) const
{
	OnDraw(target, states);
}

bool CBaseControl::OnMousePressed(sf::Event::MouseButtonEvent const &)
{
	return false;
}

bool CBaseControl::OnMouseReleased(sf::Event::MouseButtonEvent const &)
{
	return false;
}

}
