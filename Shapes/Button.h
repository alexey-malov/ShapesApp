#pragma once
#include "BaseControl.h"

enum class ButtonState {
	NORMAL,
	HOVERED,
	PRESSED
};


namespace ui
{

class CButton : public CBaseControl
{
public:
	CButton();
	void SetPosition(sf::Vector2f const & pos);
	void SetSize(sf::Vector2f const size);
protected:
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool OnMousePressed(sf::Event::MouseButtonEvent const& event) override;
	bool OnMouseReleased(sf::Event::MouseButtonEvent const& event) override;
	bool OnMouseHovered(sf::Vector2f const & pos) override;
	void ChangeColor(const ButtonState & state);
private:
	sf::RectangleShape m_background;
};

}