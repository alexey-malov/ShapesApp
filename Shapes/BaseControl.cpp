#include "stdafx.h"
#include "BaseControl.h"

using namespace sf;
using namespace std;
using boost::find;

namespace ui
{

std::shared_ptr<CBaseControl> CBaseControl::Create()
{
	return shared_ptr<CBaseControl>(new CBaseControl());
}

bool CBaseControl::OnEvent(sf::Event const & event)
{
	auto HandledEvent = [&](auto & child) {
		return child->OnEvent(event);
	};

	return any_of(m_children.rbegin(), m_children.rend(), HandledEvent)
		|| DispatchOwnEvent(event);
}

bool CBaseControl::CanBeAParent()const
{
	try
	{
		shared_from_this().get();
		return true;
	}
	catch (const bad_weak_ptr &)
	{
		m_hasDeferredChildren = true;
		return false;
	}
}

void CBaseControl::AddDeferredChildren()
{
	for (auto &it : m_children)
	{
		it->SetParent(shared_from_this());
	}
	m_hasDeferredChildren = false;
}

void CBaseControl::AppendChild(const CBaseControlPtr & control)
{
	InsertChildAtIndex(control, GetChildCount());
}

void CBaseControl::InsertChildAtIndex(const CBaseControlPtr & control, unsigned index)
{
	if (!control)
	{
		throw std::invalid_argument("Invalid control");
	}
	if (control.get() == this)
	{
		throw std::invalid_argument("Can not insert itself as a child");
	}
	if (IsItOneOfMyParents(control))
	{
		throw std::invalid_argument("Can not insert any control parent as a child");
	}

	const bool itIsMyChild = (control->GetParent().get() == this);
	if (itIsMyChild)
	{
		ChangeChildIndex(control, index);
	}
	else
	{
		AdoptChild(control, index);
	}
}

unsigned CBaseControl::GetChildCount() const
{
	return boost::numeric_cast<unsigned>(m_children.size());
}

CBaseControlPtr CBaseControl::GetChild(unsigned index) const
{
	return m_children.at(index);
}

CBaseControlPtr CBaseControl::GetParent() const
{
	return m_parent.lock();
}

void CBaseControl::RemoveFromParent()
{
	auto parent = GetParent();
	if (parent)
	{
		auto self = shared_from_this();
		parent->RemoveChild(self);
		m_parent.reset();
		OnRemovedFromParent();
	}
}

void CBaseControl::SetFrame(const sf::FloatRect & frame)
{
	if (frame != m_frame)
	{
		m_frame = frame;
		OnFrameChanged(m_frame);
	}
}

sf::FloatRect CBaseControl::GetFrame() const
{
	return m_frame;
}

sf::Vector2f CBaseControl::LocalToGlobal(const sf::Vector2f & local) const
{
	auto parent = m_parent.lock();
	auto global = parent ? parent->LocalToGlobal(local) : local;
	return GetOrigin() + global;
}

sf::Vector2f CBaseControl::GlobalToLocal(const sf::Vector2f & global) const
{
	sf::Vector2f origin = GetOrigin();
	auto parent = m_parent.lock();
	while (parent)
	{
		origin += parent->GetOrigin();
		parent = parent->GetParent();
	}
	return global - origin;
}

sf::Vector2f CBaseControl::ConvertPointFromControl(const sf::Vector2f & pt, const CBaseControlConstPtr & control) const
{
	return GlobalToLocal(control->LocalToGlobal(pt));
}

sf::Vector2f CBaseControl::ConvertPointToControl(const sf::Vector2f & pt, const CBaseControlConstPtr & control) const
{
	return control->ConvertPointFromControl(pt, shared_from_this());
}

bool CBaseControl::HitTest(sf::Vector2f const & local) const
{
	return (local.x >= 0 && local.x < m_frame.width)	// x is within the horizontal bounds
		&& (local.y >= 0 && local.y < m_frame.height);	// y is within the vertical bounds
}

void CBaseControl::OnDraw(sf::RenderTarget & /*target*/, sf::RenderStates /*states*/) const
{
}

void CBaseControl::OnFrameChanged(const sf::FloatRect & /*newFrame*/)
{
	// Can be overriden in subclasses
}

void CBaseControl::draw(RenderTarget & target, RenderStates states) const
{
	states.transform.translate({ m_frame.left, m_frame.top });
	OnDraw(target, states);

	for (auto & child : m_children)
	{
		child->draw(target, states);
	}
}

bool CBaseControl::DispatchOwnEvent(sf::Event const & event)
{
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		return OnMousePressed(event.mouseButton);
	case sf::Event::MouseButtonReleased:
		return OnMouseReleased(event.mouseButton);
	case sf::Event::Resized:
		return OnWindowResized(event.size);
	case sf::Event::MouseMoved:
		return OnMouseMoved(event.mouseMove);
	default:
		return false;
	}
}

void CBaseControl::SetParent(const CBaseControlPtr & parent)
{
	m_parent = parent;
	OnAddedToParent();
}

void CBaseControl::RemoveChild(const CBaseControlPtr & child)
{
	m_children.erase(boost::remove(m_children, child), m_children.end());
}

void CBaseControl::ChangeChildIndex(const CBaseControlPtr & control, unsigned newIndex)
{
	assert(control);
	assert(control->GetParent().get() == this);
	assert(control.get() != this);

	if (CanBeAParent() && m_hasDeferredChildren)
	{
		AddDeferredChildren();
	}

	auto src = find(m_children, control);
	assert(src != m_children.end());

	if (newIndex >= GetChildCount())
	{
		newIndex = GetChildCount() - 1;
	}

	auto dst = m_children.begin() + newIndex;
	if (src < dst)
	{
		rotate(src, src + 1, dst + 1);
	}
	else if (dst < src)
	{
		rotate(dst, src, src + 1);
	}
}

void CBaseControl::AdoptChild(const CBaseControlPtr & control, unsigned index)
{
	assert(control);
	assert(control.get() != this);
	assert(control->GetParent().get() != this);

	control->RemoveFromParent();
	if (index < m_children.size())
	{
		m_children.insert(m_children.begin() + index, control);
	}
	else
	{
		m_children.push_back(control);
	}

	if (CanBeAParent())
	{
		if (m_hasDeferredChildren)
		{
			AddDeferredChildren();
		}
		else
		{
			auto self = shared_from_this();
			control->SetParent(self);
		}
	}
}

bool CBaseControl::IsItOneOfMyParents(const CBaseControlPtr & control) const
{
	assert(control);
	for (auto parent = GetParent(); parent; parent = parent->GetParent())
	{
		if (control == parent)
		{
			return true;
		}
	}

	return false;
}

sf::Vector2f CBaseControl::GetOrigin() const
{
	return{ m_frame.left, m_frame.top };
}

bool CBaseControl::OnMousePressed(sf::Event::MouseButtonEvent const &)
{
	return false;
}

bool CBaseControl::OnMouseReleased(sf::Event::MouseButtonEvent const &)
{
	return false;
}

bool CBaseControl::OnWindowResized(sf::Event::SizeEvent const &)
{
	return false;
}

bool CBaseControl::OnMouseMoved(sf::Event::MouseMoveEvent const&)
{
	return false;
}

void CBaseControl::OnRemovedFromParent()
{
	// Can be overriden in subclasses
}

void CBaseControl::OnAddedToParent()
{
	// Can be overriden in subclasses
}
}



