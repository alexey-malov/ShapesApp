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
	/*Измененния объекта можно получить с помощью статического метода класса sf::Transformable::getTransform().
	Переменная типа sf::Transform transform, хранящаяся в классе states, хранит информацию, где должен быть отрисован объект.
	Перегруженный оператор умножения позволяет получить совммещенные измененния*/
	states.transform *= getTransform();
	target.draw(m_background, states);
}

sf::FloatRect CButton::GetBoundingRect() const
{
	/*в качестве объекта, по которому будем проверять события, выбираем m_background,
	если потребуется подключать работу камеры и некоторых других средств, метода getTransform() внутри класса-объекта будет недостаточно*/
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