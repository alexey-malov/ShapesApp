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

	void SetIcon(const std::shared_ptr<sf::Texture> & texture);
	void SetBackground(const std::shared_ptr<sf::Texture> & texture);
protected:
	CButton();
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool OnMousePressed(sf::Event::MouseButtonEvent const& event) override;
	void OnFrameChanged(const sf::FloatRect & newRect) override;
private:
	std::shared_ptr<sf::Texture> m_backgroundTexture;
	sf::RectangleShape m_background;
	std::shared_ptr<sf::Texture> m_iconTexture;
	sf::Sprite m_iconSprite;
	OnClick m_onClick;
};

}