#include "stdafx.h"
#include "..\BaseControl.h"

using namespace ui;

struct BaseControl_
{
	CBaseControlPtr control = CBaseControl::Create();
};

BOOST_FIXTURE_TEST_SUITE(BaseControl, BaseControl_)
	BOOST_AUTO_TEST_SUITE(when_constructed)
		BOOST_AUTO_TEST_CASE(has_no_parent)
		{
			BOOST_CHECK(!control->GetParent());
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()