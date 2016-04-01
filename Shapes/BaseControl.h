#pragma once

namespace ui
{

class CBaseControl;
typedef std::shared_ptr<CBaseControl> CBaseControlPtr;

class CBaseControl : public sf::Drawable
{
public:
	virtual ~CBaseControl() = default;

	bool OnEvent(sf::Event const& event);

	void InsertChild(const CBaseControlPtr & control, unsigned index = UINT_MAX);

	// Устанавливает фрейм объекта (в системе координат родителя)
	void SetFrame(const sf::FloatRect & frame);

	sf::FloatRect GetFrame()const;

protected:
	virtual bool OnMousePressed(sf::Event::MouseButtonEvent const& event);
	virtual bool OnMouseReleased(sf::Event::MouseButtonEvent const& event);
	virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void OnFrameChanged(const sf::FloatRect & newFrame);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

	bool DispatchOwnEvent(sf::Event const& event);

	std::vector<CBaseControlPtr> m_children;

	sf::FloatRect m_frame;
};
}
