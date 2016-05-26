#pragma once
#include "stdafx.h"
namespace model
{
	
struct Pointf
{
	Pointf() {};
	Pointf(float xPos, float yPos)
		: x(xPos)
		, y(yPos)
	{};
	float x;
	float y;
};

struct Frame
{
	Frame() {};
	Frame(float h, float w, Pointf const& pos)
		: height(h)
		, width(w)
		, position(pos)
	{};
	float height;
	float width;
	Pointf position;
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