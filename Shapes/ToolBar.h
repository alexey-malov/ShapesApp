#pragma once
#include "Button.h"

namespace ui
{

	class CToolBar : public ui::CBaseControl
	{
	public:
		static std::shared_ptr<CToolBar> Create(sf::Vector2u const& size);
		virtual ~CToolBar() = default;
		void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void AddChildWithIndex(const CBaseControlPtr & control, unsigned index);


	private:
		CToolBar(sf::Vector2u const& size);

		unsigned m_countChild;

		sf::RectangleShape m_background;

	};

}