#include "stdafx.h"
#include "..\BaseControl.h"

using namespace ui;

struct BaseControl_
{
	CBaseControlPtr control = CBaseControl::Create();
};

BOOST_FIXTURE_TEST_SUITE(BaseControl, BaseControl_)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(has_no_parent)
		{
			BOOST_CHECK(!control->GetParent());
		}
	BOOST_AUTO_TEST_SUITE_END()
	
	BOOST_AUTO_TEST_SUITE(on_InsertChild)
		BOOST_AUTO_TEST_CASE(becomes_a_parent_of_the_inserted_child)
		{
			auto child = CBaseControl::Create();
			control->InsertChild(child);
			auto parent = child->GetParent();
			BOOST_CHECK_EQUAL(parent, control);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()