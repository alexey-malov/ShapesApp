#pragma once
#include "BaseControl.h"

namespace ui
{

class CButton : public CBaseControl
{
public:
	CButton();

protected:
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool OnMousePressed(sf::Event::MouseButtonEvent const& event) override;

	sf::FloatRect GetBoundingRect() const override;

private:
	sf::RectangleShape m_background;
};

}