#include "stdafx.h"
#include "Button.h"

using namespace sf;

namespace ui
{

CButton::CButton()
	: m_background({ 100, 30 })
{
}

void CButton::OnDraw(sf::RenderTarget & target, sf::RenderStates states) const
{
	/*���������� ������� ����� �������� � ������� ������������ ������ ������ sf::Transformable::getTransform().
	���������� ���� sf::Transform transform, ���������� � ������ states, ������ ����������, ��� ������ ���� ��������� ������.
	������������� �������� ��������� ��������� �������� ������������ ����������*/
	states.transform *= getTransform();
	target.draw(m_background, states);
}

sf::FloatRect CButton::GetBoundingRect() const
{
	/*� �������� �������, �� �������� ����� ��������� �������, �������� m_background,
	���� ����������� ���������� ������ ������ � ��������� ������ �������, ������ getTransform() ������ ������-������� ����� ������������*/
	return getTransform().transformRect(m_background.getGlobalBounds()); 
}

bool CButton::OnMousePressed(sf::Event::MouseButtonEvent const & event)
{
	sf::Vector2f pt(float(event.x), float(event.y));
	if (GetBoundingRect().contains(pt))
	{
		// TODO: action.
		return true;
	}
	return false;
}

}