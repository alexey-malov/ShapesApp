#include "stdafx.h"
#include "..\BaseControl.h"

using namespace ui;
using namespace std;

using boost::algorithm::all_of;


struct BaseControl_
{
	CBaseControlPtr control = CBaseControl::Create();
	CBaseControlPtr parent = CBaseControl::Create();
	const vector<CBaseControlPtr> children = { CBaseControl::Create(), CBaseControl::Create(), CBaseControl::Create() };

	template <typename Range>
	void ExpectChildren(const Range & expectedChildren)
	{
		BOOST_REQUIRE_EQUAL(control->GetChildCount(), expectedChildren.size());
		unsigned index = 0;
		for (auto & expectedChild : expectedChildren)
		{
			BOOST_CHECK_EQUAL(control->GetChild(index++), expectedChild);
		}
	}
};

BOOST_FIXTURE_TEST_SUITE(BaseControl, BaseControl_)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(has_no_parent)
		{
			BOOST_CHECK(!control->GetParent());
		}
		BOOST_AUTO_TEST_CASE(has_no_children)
		{
			BOOST_CHECK_EQUAL(control->GetChildCount(), 0u);
		}
	BOOST_AUTO_TEST_SUITE_END()
	
	struct after_inserting_children_ : BaseControl_
	{
		after_inserting_children_()
		{ 
			unsigned index = 0;
			for (auto & child : children)
			{
				control->InsertChildAtIndex(child, index++);
				BOOST_CHECK_EQUAL(control->GetChildCount(), index);
			}
		}
	};
	BOOST_FIXTURE_TEST_SUITE(after_inserting_children, after_inserting_children_)
		BOOST_AUTO_TEST_CASE(has_child_count_equal_to_number_of_added_children)
		{
			BOOST_CHECK_EQUAL(control->GetChildCount(), children.size());
		}
		BOOST_AUTO_TEST_CASE(becomes_their_parent)
		{
			BOOST_CHECK(all_of(children, [=](auto & child) {
				return child->GetParent() == control; 
			}));
		}
		BOOST_AUTO_TEST_CASE(allows_retrieving_children_by_index)
		{
			for (unsigned i = 0; i < children.size(); ++i)
			{
				BOOST_CHECK_EQUAL(control->GetChild(i), children[i]);
			}
		}
		BOOST_AUTO_TEST_CASE(throws_out_of_range_when_trying_to_get_child_at_wrong_index)
		{
			BOOST_CHECK_THROW(control->GetChild(boost::numeric_cast<unsigned>(children.size())), out_of_range);
		}
		BOOST_AUTO_TEST_CASE(can_insert_a_child_in_the_beginning)
		{
			auto child = CBaseControl::Create();
			control->InsertChildAtIndex(child, 0);
			auto expectedChildren(children);
			expectedChildren.insert(expectedChildren.begin(), child);
			ExpectChildren(expectedChildren);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(can_append_children_to_the_end_of_the_children_list)
	{
		for (auto & child : children)
		{
			auto childCount = control->GetChildCount();
			control->AppendChild(child);
			BOOST_REQUIRE_EQUAL(control->GetChildCount(), childCount + 1);
			BOOST_CHECK_EQUAL(control->GetChild(childCount), child);
		}
	}

	struct being_a_child_ : BaseControl_
	{
		being_a_child_() 
		{
			parent->InsertChildAtIndex(control, 0); 
		}
	};
	BOOST_FIXTURE_TEST_SUITE(being_a_child, being_a_child_)
		BOOST_AUTO_TEST_CASE(can_be_removed_from_parent)
		{
			control->RemoveFromParent();
			BOOST_CHECK(!control->GetParent());
			BOOST_CHECK_EQUAL(parent->GetChildCount(), 0u);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()