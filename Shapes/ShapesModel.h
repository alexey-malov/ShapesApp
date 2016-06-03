#pragma once
#include "stdafx.h"
namespace model
{
	
struct Pointf
{
	Pointf() = default;
	Pointf(float xPos, float yPos)
		: x(xPos)
		, y(yPos)
	{}
	float x = 0;
	float y = 0;
};

struct Frame
{
	Frame() = default;
	Frame(float h, float w, Pointf const& pos)
		: height(h)
		, width(w)
		, position(pos)
	{};
	float height = 0;
	float width = 0;
	Pointf position = Pointf(0, 0);
};

struct IShape
{
	virtual Frame GetFrame() = 0;
	virtual void SetFrame(Frame const& frame) = 0;
	virtual ~IShape() = default;
};

class CAbstractShape : public IShape
{
public:
	CAbstractShape();
	Frame GetFrame() override;
	void SetFrame(Frame const& frame) override;

private:
	Frame m_frame;
};

}