#pragma once

namespace ui
{

class CBaseControl;
typedef std::shared_ptr<CBaseControl> CBaseControlPtr;

class CBaseControl 
	: public sf::Drawable
	, public std::enable_shared_from_this<CBaseControl>
{
public:
	static std::shared_ptr<CBaseControl> Create();

	virtual ~CBaseControl() = default;

	bool OnEvent(sf::Event const& event);

	void InsertChild(const CBaseControlPtr & control, unsigned index = UINT_MAX);
	CBaseControlPtr GetParent()const;
	void RemoveFromParent();

protected:
	// Конструктор защищен, чтобы требовать создания
	// объекта исключительно в куче (этого требует наследование от shared_from_this)
	CBaseControl() = default;

	virtual bool OnMousePressed(sf::Event::MouseButtonEvent const& event);
	virtual bool OnMouseReleased(sf::Event::MouseButtonEvent const& event);
	virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

	bool DispatchOwnEvent(sf::Event const& event);
	void SetParent(const CBaseControlPtr & parent);
	void RemoveChild(const CBaseControlPtr & child);

	std::vector<CBaseControlPtr> m_children;
	std::weak_ptr<CBaseControl> m_parent;
};
}
