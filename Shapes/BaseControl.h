#pragma once
#include "BaseControlContainer.h"

namespace ui
{

class CBaseControl;
typedef std::shared_ptr<CBaseControl> CBaseControlPtr;
typedef std::shared_ptr<const CBaseControl> CBaseControlConstPtr;
/*!
	\brief Base class - root of tree application ui structure

	Class, that able to be drawn, control coming events, same as mouse click-move events,
	have tools to set frame of objects, convert points to different coordinate systems,
	as a root of tree - able to add and remove children accessible from container variable.
	Delegate some functionality to provide overriding for all inheritors.
	Derived from IBaseControlContainer
*/
class CBaseControl 
	: public sf::Drawable
	, public std::enable_shared_from_this<CBaseControl>
	, public ui::IBaseControlContainer
{
	//! Copy-constructor of CBaseControl
	/*!
		Delete(disable)
	*/
	CBaseControl(const CBaseControl &) = delete;

	//! Copy-assignmen operator of CBaseControl
	/*!
		Delete(disable)
	*/
	CBaseControl& operator = (const CBaseControl &) = delete;
public:
	//! Static member, creating instance of class and returning shared pointer on it
	//! \return Shared pointer on CBaseControl instance
	static std::shared_ptr<CBaseControl> Create();

	/*! 
	  Virtual member function, overriden from IBaseControlContainer, starting recursion, that sent event to all children,
	  and return true, if event was dispatched
	  Can be ovveriden by inheritors

	  \param event is sf::Event argument
	  \return bool - result of dispatching event
	*/
	bool OnEvent(sf::Event const& event) override;

	/*!
	  Normal member function taking pointer to child and appending it 
	  at the end of children container

	  \param control is referens to CBaseControlPtr, appending child, argument
	*/
	void AppendChild(const CBaseControlPtr & control);

	/*!
	  Normal member function taking pointer to child and position to insert.
	  Appends child at the specified position of children container

	  \throw throw std::invalid_argument If taking invalid control
	  \throw std::invalid_argument If taking itself as argument
	  \throw std::invalid_argument If taking any of parent control
	  \param control is referens to CBaseControlPtr,  appending child, argument
	  \param index is unsigned argument, position of child insert
	*/
	void InsertChildAtIndex(const CBaseControlPtr & control, unsigned index);

	//! Const member function, returning children counter of current father
	/*!
	  \return unsigned - count of children
	*/
	unsigned GetChildCount()const;

	//! Const member function, taking index of child and returning shared pointer on it
	/*!
	  \param index is unsigned index of child
	  \return CBaseControlPtr - std::shared_ptr<CBaseControl> - child
	*/
	CBaseControlPtr GetChild(unsigned index) const;

	//! Const member function, returning weak pointer on father control
	/*!
	  \return std::weak_ptr<CBaseControl> - child
	*/
	CBaseControlPtr GetParent()const;
	
	//! Normal member function, removing this instance of class from parent
	void RemoveFromParent();
	
	/*!
	  Normal member function, taking reference on rectagle frame
	  with coordinate and dimensions and setting by it frame of class

	  \param frame is reference on sf::FloatRect argument
	*/
	void SetFrame(const sf::FloatRect & frame);

	//! Const member function, returning current frame of class
	//! \return sf::FloatRect - current frame of class
	sf::FloatRect GetFrame()const;

	//! Const member function, returning current origin of class
	//! \return sf::Vector2f - current origin of class
	sf::Vector2f GetOrigin()const;
	
	/*! 
	  Const member function, returning coordinates taken point in global coordinate system,
	  in respect with parent coordinate system

	  \param local is sf::Vector2f - coordinates of point in local cooridnate system
	  \return sf::Vector2f coordinates of point in global cooridnate system
	*/
	sf::Vector2f LocalToGlobal(const sf::Vector2f & local) const;

	/*! 
	  Const member function, returning coordinates taken point in local coordinate system
	  of current control, in respect with parent coordinate system

	  \param global is sf::Vector2f - coordinates of point in global cooridnate system
	  \return sf::Vector2f coordinates of point in local cooridnate system of current control
	*/
	sf::Vector2f GlobalToLocal(const sf::Vector2f & global) const;
	
	/*!
	  Const member function, returning coordinates taken point in
	  local coordinate system taken control in local coordinate system this control
	  of current control

	  \param pt is sf::Vector2f - coordinates of point in local cooridnate system of other control
	  \param control is const reference on shared_ptr<CBaseControl> - other control
	  \return sf::Vector2f coordinates of point in local cooridnate system of this control
	*/
	sf::Vector2f ConvertPointFromControl(const sf::Vector2f & pt, const CBaseControlConstPtr& control) const;

	/*!
	  Const member function, returning coordinates taken point
	  coordinate system of current control in coordinate system of taken control

	  \param pt is sf::Vector2f - coordinates of point in local cooridnate system of this control
	  \param control is const reference on shared_ptr<CBaseControl> - other control
	  \return sf::Vector2f coordinates of point in local cooridnate system of other control
	*/
	sf::Vector2f ConvertPointToControl(const sf::Vector2f & pt, const CBaseControlConstPtr& control) const;

	/*!
	  Const virtual member function, taking point coordinate and returning bool result of check
	  - hit point in frame of this control in local coordinate system
	  Can be overriden by inheritors

	  \param local is sf::Vector2f - coordinates of point
	  \return bool retrun true if point hit in frame
	*/
	virtual bool HitTest(sf::Vector2f const & local) const;

	//! Virtual destructor of CBaseControl
	/*!
	  Compiler generate it by default
	*/
	virtual ~CBaseControl() = default;

protected:
	CBaseControl() = default;
	virtual void OnRemovedFromParent();
	virtual void OnAddedToParent();
	virtual bool OnWindowResized(sf::Event::SizeEvent const& event);
	virtual bool OnMousePressed(sf::Event::MouseButtonEvent const& event);
	virtual bool OnMouseReleased(sf::Event::MouseButtonEvent const& event);
	virtual bool OnMouseMoved(sf::Event::MouseMoveEvent const& event);
	virtual void OnMouseOver(sf::Event::MouseMoveEvent const&) {};
	virtual void OnMouseLeave(sf::Event::MouseMoveEvent const&) {};
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
	bool CanBeAParent() const;
	void AddDeferredChildren();

	std::vector<CBaseControlPtr> m_children;
	std::weak_ptr<CBaseControl> m_parent;
	sf::FloatRect m_frame;
	mutable bool m_hasDeferredChildren = false;
};
}
