#include "stdafx.h"
#include "Triangle.h"


model::CTriangle::CTriangle()
{
}

void model::CTriangle::SetFrame(Frame const & frame)
{
	CAbstractShape::SetFrame(frame);
	SetPicks();
}

model::TrianglePicks model::CTriangle::GetPicks()
{
	return m_picks;
}

void model::CTriangle::SetPicks()
{
	auto frame = GetFrame();
	m_picks.firstPick = frame.position;
	m_picks.secondPick = Pointf(frame.position.x + (frame.width / 2), frame.position.y + frame.height);
	m_picks.thirdPick = Pointf(frame.position.x + frame.width, frame.position.y);
}
