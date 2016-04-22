#pragma once

namespace ui
{ 

class IBaseControlContainer
{
public:
	virtual ~IBaseControlContainer() = default;
	
	virtual bool OnEvent(sf::Event const& event) = 0;
};

}