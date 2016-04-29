#pragma once
#include "BaseControlContainer.h"

namespace ui
{

class CBaseControl;
typedef std::shared_ptr<CBaseControl> CBaseControlPtr;
typedef std::shared_ptr<const CBaseControl> CBaseControlConstPtr;

class CBaseControl 
	: public sf::Drawable
	, public std::enable_shared_from_this<CBaseControl>
	, public ui::IBaseControlContainer
{
	CBaseControl(const CBaseControl &) = delete;
	CBaseControl& operator = (const CBaseControl &) = delete;
public:
	static std::shared_ptr<CBaseControl> Create();

	bool OnEvent(sf::Event const& event) override;

	void AppendChild(const CBaseControlPtr & control);
	void InsertChildAtIndex(const CBaseControlPtr & control, unsigned index);
	unsigned GetChildCount()const;
	CBaseControlPtr GetChild(unsigned index) const;

	CBaseControlPtr GetParent()const;
	void RemoveFromParent();
	
	void SetFrame(const sf::FloatRect & frame);
	sf::FloatRect GetFrame()const;

	sf::Vector2f GetOrigin()const;
	
	sf::Vector2f LocalToGlobal(const sf::Vector2f & local) const;
	sf::Vector2f GlobalToLocal(const sf::Vector2f & global) const;
	
	sf::Vector2f ConvertPointFromControl(const sf::Vector2f & pt, const CBaseControlConstPtr& control) const;
	sf::Vector2f ConvertPointToControl(const sf::Vector2f & pt, const CBaseControlConstPtr& control) const;

	virtual bool HitTest(sf::Vector2f const & local)const ;

	virtual ~CBaseControl() = default;

protected:
	CBaseControl() = default;

	virtual bool OnWindowResized(sf::Event::SizeEvent const& event);
	virtual bool OnMousePressed(sf::Event::MouseButtonEvent const& event);
	virtual bool OnMouseReleased(sf::Event::MouseButtonEvent const& event);
	virtual bool OnMouseMoved(sf::Event::MouseMoveEvent const& event);
	virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void OnFrameChanged(const sf::FloatRect & newFrame);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

	bool DispatchOwnEvent(sf::Event const& event);
	void SetParent(const CBaseControlPtr & parent);
	void RemoveChild(const CBaseControlPtr & child);
	void ChangeChildIndex(const CBaseControlPtr & control, unsigned newIndex);
	void AdoptChild(const CBaseControlPtr & control, unsigned index);
	bool IsItOneOfMyParents(const CBaseControlPtr & control)const;

	std::vector<CBaseControlPtr> m_children;
	std::weak_ptr<CBaseControl> m_parent;
	sf::FloatRect m_frame;
};
}
