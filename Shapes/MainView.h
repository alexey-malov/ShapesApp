#pragma once
#include "ToolBar.h"

namespace ui
{

class CMainView
	: public ui::CBaseControl
{
public:
	static std::shared_ptr<CMainView> Create();

	void AddChildWithIndex(unsigned index, sf::Vector2u const &size);

	void CreateMainToolbar();
private:
	bool OnWindowResized(sf::Event::SizeEvent const& event) override;
	std::shared_ptr<CToolBar> GetToolbar(unsigned index);

private:
	std::map<unsigned, std::shared_ptr<CToolBar>> m_toolbars;
};

}