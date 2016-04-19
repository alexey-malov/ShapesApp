#pragma once
#include "BaseControl.h"
#include "Signals.h"
#include "Background.h"
namespace ui
{

class CButton : public CBaseControl
{
	typedef Signal<void()> OnClick;
public:
	static std::shared_ptr<CButton> Create();
	void SetBackground(std::shared_ptr<IBackground> const& background);
	Connection DoOnClick(OnClick::slot_type const &handler);

protected:
	CButton();
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool OnMousePressed(sf::Event::MouseButtonEvent const& event) override;
private:
	std::shared_ptr<IBackground> m_background;
	OnClick m_onClick;
};

}