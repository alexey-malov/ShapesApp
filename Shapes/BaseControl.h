#pragma once

namespace ui
{
class CBaseControl : public sf::Drawable
{
public:
	virtual ~CBaseControl() = default;

	bool OnEvent(sf::Event const& event);

protected:
	virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

protected:
	virtual bool OnMousePressed(sf::Event::MouseButtonEvent const& event);
	virtual bool OnMouseReleased(sf::Event::MouseButtonEvent const& event);
};
}
