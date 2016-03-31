#pragma once
#include "BaseControl.h"
#include <boost/signals2.hpp>

namespace ui
{

class CButton : public CBaseControl
{
	typedef boost::signals2::signal<void()> OnClick;
	typedef OnClick::slot_type OnClickSlotType;
	typedef boost::signals2::connection Connection;
public:
	CButton();

	Connection DoOnClick(OnClickSlotType const &handler);

protected:
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool OnMousePressed(sf::Event::MouseButtonEvent const& event) override;

private:
	sf::RectangleShape m_background;
	OnClick m_onClick;
};

}