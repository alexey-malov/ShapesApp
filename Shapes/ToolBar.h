#pragma once
#include "Button.h"
#include "ToolbarButton.h"

namespace ui
{

	class CToolBar : public ui::CBaseControl
	{
	public:
		static std::shared_ptr<CToolBar> Create(sf::Vector2u const& size);
		virtual ~CToolBar() = default;
		void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void AddChildWithIndex(unsigned index);

		std::shared_ptr<CToolbarButton> GetButton(unsigned const& index);

		void SetButtonsBackgrounds(const std::shared_ptr<sf::Texture> & texture);

	private:
		CToolBar(sf::Vector2u const& size);

		unsigned m_countChild;

		std::map<unsigned, std::shared_ptr<CToolbarButton>> m_buttons;

		sf::RectangleShape m_background;

	};

}