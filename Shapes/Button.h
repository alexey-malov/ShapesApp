#pragma once
#include "BaseControl.h"
#include "Signals.h"

namespace ui
{

class CButton : public CBaseControl
{
	typedef Signal<void()> OnClick;
public:
	static std::shared_ptr<CButton> Create();

	Connection DoOnClick(OnClick::slot_type const &handler);
	void SetBackground(std::shared_ptr<sf::Texture>);
protected:
	CButton();
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool OnMousePressed(sf::Event::MouseButtonEvent const& event) override;

private:
	sf::RectangleShape m_background;
	sf::Texture	m_backgroundTexture;
	OnClick m_onClick;
};

}