#pragma once
#include "stdafx.h"
#include "BaseControl.h"

namespace ui
{

class CShapeView : public CBaseControl
{
public:
	CShapeView(sf::FloatRect const & frame);
private:
	sf::FloatRect m_frame;
};

}

