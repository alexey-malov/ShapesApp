#include "stdafx.h"
#include "Button.h"

using namespace sf;

namespace ui
{



void CButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	RectangleShape rs({ 20, 30 });
	target.draw(rs, states);

	target;
	states;
}

}