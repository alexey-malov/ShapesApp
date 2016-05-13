#pragma once
#include "ToolBar.h"

#include "Image.h"

namespace ui
{

class CMainView
	: public ui::CBaseControl
{
public:
	static std::shared_ptr<CMainView> Create();

	void AddChildWithIndex(unsigned index, sf::Vector2u const &size);

	void CreateMainToolbar();
protected:
	void OnDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	bool OnWindowResized(sf::Event::SizeEvent const& event) override;
	std::shared_ptr<CToolBar> GetToolbar(unsigned index);

	CMainView();

private:
	std::map<unsigned, std::shared_ptr<CToolBar>> m_toolbars;

	std::unique_ptr<IImage2> m_texturedImage;
};

}