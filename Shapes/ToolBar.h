#pragma once
#include "Button.h"
#include "ToolbarButton.h"

namespace ui
{

class CToolBar : public ui::CBaseControl
{
public:
	static std::shared_ptr<CToolBar> Create(sf::Vector2u const& size);

	std::shared_ptr<IToolbarButton> AddChildWithIndex(unsigned index);

	std::shared_ptr<IToolbarButton> GetButton(unsigned index);

	void SetButtonsBackgrounds(const std::shared_ptr<sf::Texture> & texture);
	
	sf::Vector2f GetToolbarSize()const;
	void SetToolbarSize(sf::Vector2f const &size);

	void SetRightIndentSize(float width);
	float GetRightIndentSize()const;


protected:
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	CToolBar(sf::Vector2u const& size);

	unsigned m_countChild;

	std::map<unsigned, std::shared_ptr<CToolbarButton>> m_buttons;

	sf::RectangleShape m_background;

	float m_rightIndentSize = 0;

};

}