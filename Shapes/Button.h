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

	void SetIcon(const std::shared_ptr<sf::Texture> & texture);
	void SetBackground(const std::shared_ptr<sf::Texture> & texture);
protected:
	CButton();
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool OnMousePressed(sf::Event::MouseButtonEvent const& event) override;
	void OnFrameChanged(const sf::FloatRect & newRect) override;
	bool OnMouseReleased(sf::Event::MouseButtonEvent const& event) override;
	void OnMouseOver(sf::Event::MouseMoveEvent const& event) override;
	void OnMouseLeave(sf::Event::MouseMoveEvent const& event) override;
	void ChangeColor(const ButtonState & state);
private:
	bool MouseHitTest(const sf::Vector2i & mousePos)const;

	std::shared_ptr<sf::Texture> m_backgroundTexture;
	sf::RectangleShape m_background;
	std::shared_ptr<sf::Texture> m_iconTexture;
	sf::Sprite m_iconSprite;
	OnClick m_onClick;
	bool m_isPressed = false;
};

}