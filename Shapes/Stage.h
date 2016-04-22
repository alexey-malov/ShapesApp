#pragma once
#include "MainView.h"
#include "BaseControlContainer.h"

namespace ui
{ 

class CStage
	: public ui::IBaseControlContainer
{
public:
	CStage(std::unique_ptr<sf::RenderWindow> && window);
	void Execute();

	CBaseControlPtr GetRoot() const;

private:
	bool OnEvent(sf::Event const& event) override;

private:
	ui::CBaseControlPtr m_root;
	std::unique_ptr<sf::RenderWindow> m_window;
	sf::View m_view;
};

}