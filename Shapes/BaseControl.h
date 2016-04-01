#pragma once

namespace ui
{

class CBaseControl;
typedef std::shared_ptr<CBaseControl> CBaseControlPtr;

class CBaseControl : public sf::Drawable
{
public:
	virtual ~CBaseControl() = default;

	virtual bool OnEvent(sf::Event const& event);

	void InsertChild(const CBaseControlPtr & control, unsigned index = UINT_MAX);

protected:
	virtual bool OnMousePressed(sf::Event::MouseButtonEvent const& event);
	virtual bool OnMouseReleased(sf::Event::MouseButtonEvent const& event);
	virtual bool OnMouseHovered(sf::Event::MouseMoveEvent const& event);
	virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

	bool DispatchOwnEvent(sf::Event const& event);

	std::vector<CBaseControlPtr> m_children;
};
}
