#pragma once
#include "MainView.h"
#include "BaseControlContainer.h"

namespace ui
{ 

class CStage
	: public ui::IBaseControlContainer
{
public:
	CStage();
	void Execute();

private:
	bool OnEvent(sf::Event const& event) override;

private:
	ui::CBaseControlPtr m_pRoot;
	sf::RenderWindow m_window;
	sf::View m_view;
};

}