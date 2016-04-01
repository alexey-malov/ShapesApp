#pragma once
#include "BaseControl.h"

namespace ui
{

class CButton : public CBaseControl
{
public:
	CButton(std::string const& name, sf::Vector2f const& pos);

protected:
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool OnMousePressed(sf::Event::MouseButtonEvent const& event) override;

private:
	sf::RectangleShape m_background;

	sf::Vector2f m_buttonPos;

	std::string m_buttonName;
};

}