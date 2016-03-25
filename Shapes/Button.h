#pragma once

namespace ui
{

class CButton : public sf::Drawable
{
public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}