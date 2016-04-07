#pragma once
#include "BaseControl.h"
#include "Signals.h"

enum class ButtonState {
	NORMAL,
	HOVERED,
	PRESSED
};

namespace ui
{

class CButton : public CBaseControl
{
	typedef Signal<void()> OnClick;
public:
	static std::shared_ptr<CButton> Create();

	Connection DoOnClick(OnClick::slot_type const &handler);

protected:
	CButton();
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool OnMousePressed(sf::Event::MouseButtonEvent const& event) override;
	bool OnMouseReleased(sf::Event::MouseButtonEvent const& event) override;
	bool OnMouseHovered(sf::Event::MouseMoveEvent const& event) override;
	void ChangeColor(const ButtonState & state);

private:
	sf::RectangleShape m_background;
	OnClick m_onClick;
	bool isPressed = false;
};

}