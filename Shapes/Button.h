#pragma once
#include "BaseControl.h"
#include "Signals.h"

namespace ui
{

class CButton : public CBaseControl
{
	typedef Signal<void()> OnClick;
public:
	CButton();

	Connection DoOnClick(OnClick::slot_type const &handler);

protected:
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool OnMousePressed(sf::Event::MouseButtonEvent const& event) override;
	void OnFrameChanged(const sf::FloatRect & newRect) override;
private:
	sf::RectangleShape m_background;
	OnClick m_onClick;
};

}