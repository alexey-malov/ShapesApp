#pragma once
#include "ShapeView.h"
#include "BaseControl.h"

namespace ui
{
class CSheet : public CBaseControl
{
public:
	static std::shared_ptr<CSheet> Create(sf::FloatRect const& frame);
protected:
	void OnDraw(sf::RenderTarget & target, sf::RenderStates states) const override;
	void OnFrameChanged(const sf::FloatRect & newFrame) override ;
private:
	CSheet(sf::FloatRect const& frame);
	sf::RectangleShape m_background;
};

class CCanvas
{
public:
	static std::shared_ptr<CCanvas> Create(sf::FloatRect const& frame);

	void Insert(std::shared_ptr<CShapeView> const & shape, unsigned index);
	std::shared_ptr<CShapeView> GetShape(unsigned index);

	void SetFrame(sf::FloatRect const & newFrame);

	std::shared_ptr<CSheet> GetSheet();
private:
	CCanvas(sf::FloatRect const& frame);
	
	std::shared_ptr<CSheet> m_sheet;

	std::vector<std::shared_ptr<CShapeView>> m_shapes;
};

}