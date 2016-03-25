#include "stdafx.h"
#include "BaseControl.h"

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

bool CBaseControl::OnMousePressed(sf::Event::MouseButtonEvent const &)
{
	return false;
}

bool CBaseControl::OnMouseReleased(sf::Event::MouseButtonEvent const &)
{
	return false;
}

}
