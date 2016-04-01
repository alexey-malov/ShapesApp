#pragma once
#include "Button.h"

namespace ui
{
	typedef std::shared_ptr<ui::CButton> CButtonPtr;

	class CToolBar : public sf::Drawable
	{
	public:
		CToolBar(sf::RenderWindow & window);

		virtual ~CToolBar() = default;

		virtual void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const;

		void InsertChild(const CButtonPtr & control);

		void OnEvent(sf::Event const& event);

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

		std::vector<CButtonPtr> m_children;

		sf::RectangleShape m_background;

		sf::RenderWindow & m_targetWindow;
	};

}
