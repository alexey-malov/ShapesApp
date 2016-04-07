#pragma once
#include "Button.h"

namespace ui
{

	class CToolBar : public ui::CBaseControl
	{
	public:
		CToolBar(sf::RenderWindow & window);
		virtual ~CToolBar() = default;
		void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;


	private:

		std::vector<CBaseControlPtr> m_children;

		sf::RectangleShape m_background;

	};

}