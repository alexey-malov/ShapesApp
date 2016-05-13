#pragma once
#include "stdafx.h"
namespace ui
{
	
	typedef std::pair<float, float> Pointf;
	typedef unsigned char Uint8;

	struct SColor
	{
		SColor(Uint8 const& r, Uint8 const& g, Uint8 const& b, Uint8 const& o = 255)
			: red(r)
			, green(g)
			,blue(b)
			, opacity(o)
		{
		}
		Uint8 red;
		Uint8 green;
		Uint8 blue;
		Uint8 opacity;

	};

struct IShape
{
	virtual Pointf GetPosition() = 0;
	virtual void SetPosition(Pointf const& position) = 0;

	virtual SColor GetFillColor() = 0;
	virtual void SetFillColor(SColor const& color) = 0;

	virtual SColor GetBorderColor() = 0;
	virtual void SetBorderColor(SColor const& color) = 0;

	virtual Pointf GetScale() = 0;
	virtual void SetScale(Pointf const& scale) = 0;

	virtual float GetBorderSize() = 0;
	virtual void SetBorderSize(float const& borderWidth) = 0;
};

class CAbstractShape : public IShape
{
public:
	CAbstractShape();

	Pointf GetPosition() override;
	void SetPosition(Pointf const& position) override;

	SColor GetFillColor() override;
	void SetFillColor(SColor const& color) override;

	SColor GetBorderColor() override;
	void SetBorderColor(SColor const& color) override;

	Pointf GetScale() override;
	void SetScale(Pointf const& scale) override;

	float GetBorderSize() override;
	void SetBorderSize(float const& borderWidth) override;
private:
	Pointf m_position;
	Pointf m_scale;
	Pointf m_origin;
	float m_rotation;
	float m_borderWidth;

	SColor m_fillColor;
	SColor m_borderColor;
};
}