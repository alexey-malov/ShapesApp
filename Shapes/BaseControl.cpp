#include "stdafx.h"
#include "BaseControl.h"

using namespace sf;
using namespace std;

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

void CBaseControl::InsertChild(const CBaseControlPtr & control, unsigned index)
{

	if (index < m_children.size())
	{
		m_children.insert(m_children.begin() + index, control);
	}
	else
	{
		m_children.push_back(control);
	}

	auto self = shared_from_this();
	control->RemoveFromParent();
	control->SetParent(self);
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
	}
}

void CBaseControl::OnDraw(sf::RenderTarget & /*target*/, sf::RenderStates /*states*/) const
{
}

void CBaseControl::draw(RenderTarget & target, RenderStates states) const
{
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
	default:
		return false;
	}
}

void CBaseControl::SetParent(const CBaseControlPtr & parent)
{
	m_parent = parent;
}

void CBaseControl::RemoveChild(const CBaseControlPtr & child)
{
	m_children.erase(boost::remove(m_children, child), m_children.end());
}

bool CBaseControl::OnMousePressed(sf::Event::MouseButtonEvent const &)
{
	return false;
}

bool CBaseControl::OnMouseReleased(sf::Event::MouseButtonEvent const &)
{
	return false;
}

}
