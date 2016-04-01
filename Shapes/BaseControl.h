#pragma once

namespace ui
{

class CBaseControl;
typedef std::shared_ptr<CBaseControl> CBaseControlPtr;

class CBaseControl : public sf::Drawable, public sf::Transformable
{
public:
	virtual ~CBaseControl() = default;

	bool OnEvent(sf::Event const& event);

	void InsertChild(const CBaseControlPtr & control, unsigned index = UINT_MAX);

protected:
	virtual bool OnMousePressed(sf::Event::MouseButtonEvent const& event);
	virtual bool OnMouseReleased(sf::Event::MouseButtonEvent const& event);
	virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const;

	/*метод необходимый дл€ реализации кликов по элементам,
	т.к. теперь наши кнопки сами по себе €вл€ютс€ трансформируемыми объектами
	(перегружать в наследниках)*/
	virtual sf::FloatRect GetBoundingRect() const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

	bool DispatchOwnEvent(sf::Event const& event);

	std::vector<CBaseControlPtr> m_children;
};
}
