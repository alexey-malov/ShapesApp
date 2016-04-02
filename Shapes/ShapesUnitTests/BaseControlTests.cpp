#include "stdafx.h"
#include "..\BaseControl.h"

using namespace ui;
using namespace std;

using boost::algorithm::all_of;


struct BaseControl_
{
	CBaseControlPtr control = CBaseControl::Create();
	CBaseControlPtr parent = CBaseControl::Create();
	CBaseControlPtr grandParent = CBaseControl::Create();
	const vector<CBaseControlPtr> children = { CBaseControl::Create(), CBaseControl::Create(), CBaseControl::Create(), CBaseControl::Create()};

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
		BOOST_AUTO_TEST_CASE(updates_child_count)
		{
			BOOST_CHECK_EQUAL(control->GetChildCount(), children.size());
		}
		BOOST_AUTO_TEST_CASE(becomes_a_parent_of_each_added_child)
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
		BOOST_AUTO_TEST_CASE(forbids_getting_a_child_by_wrong_index)
		{
			BOOST_CHECK_THROW(control->GetChild(boost::numeric_cast<unsigned>(children.size())), out_of_range);
		}
		BOOST_AUTO_TEST_CASE(can_insert_a_child_at_any_position)
		{
			deque<CBaseControlPtr> expectedChildren(children.begin(), children.end());
			{
				auto frontChild = CBaseControl::Create();
				auto midChild = CBaseControl::Create();
				auto backChild = CBaseControl::Create();
				control->InsertChildAtIndex(frontChild, 0);
				control->InsertChildAtIndex(midChild, 1);
				control->InsertChildAtIndex(backChild, control->GetChildCount());

				expectedChildren.push_front(midChild);
				expectedChildren.push_front(frontChild);
				expectedChildren.push_back(backChild);
			}

			ExpectChildren(expectedChildren);
		}

		struct can_move_its_child_ : after_inserting_children_
		{
			can_move_its_child_()
			{
				BOOST_REQUIRE_EQUAL(children.size(), 4);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(can_move_its_child, can_move_its_child_)
			BOOST_AUTO_TEST_CASE(forward)
			{
				control->InsertChildAtIndex(control->GetChild(0), 2);
				ExpectChildren(vector<CBaseControlPtr>{children[1], children[2], children[0], children[3]});
			}
			BOOST_AUTO_TEST_CASE(backward)
			{
				control->InsertChildAtIndex(control->GetChild(3), 0);
				ExpectChildren(vector<CBaseControlPtr>{children[3], children[0], children[1], children[2]});
			}
			BOOST_AUTO_TEST_CASE(to_the_end)
			{
				control->InsertChildAtIndex(control->GetChild(0), 4);
				ExpectChildren(vector<CBaseControlPtr>{children[1], children[2], children[3], children[0]});
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_CASE(does_nothing_when_inserting_existing_child_at_its_position)
		{
			BOOST_REQUIRE_EQUAL(children.size(), 4);
			control->InsertChildAtIndex(control->GetChild(3), 3);
			ExpectChildren(children);
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

	BOOST_AUTO_TEST_SUITE(does_not_allow_inserting)
		BOOST_AUTO_TEST_CASE(itself_as_a_child)
		{
			BOOST_CHECK_THROW(control->AppendChild(control), invalid_argument);
			BOOST_CHECK_EQUAL(control->GetChildCount(), 0u);
			BOOST_CHECK(!control->GetParent());
		}
		BOOST_AUTO_TEST_CASE(null_ptr_child)
		{
			BOOST_CHECK_THROW(control->AppendChild(nullptr), invalid_argument);
			BOOST_CHECK_EQUAL(control->GetChildCount(), 0u);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct being_a_child_ : BaseControl_
	{
		being_a_child_() 
		{
			grandParent->AppendChild(parent);
			parent->AppendChild(control); 
		}
	};
	BOOST_FIXTURE_TEST_SUITE(being_a_child, being_a_child_)
		BOOST_AUTO_TEST_CASE(can_be_removed_from_parent)
		{
			control->RemoveFromParent();
			BOOST_CHECK(!control->GetParent());
			BOOST_CHECK_EQUAL(parent->GetChildCount(), 0u);
		}
		BOOST_AUTO_TEST_CASE(does_not_allow_inserting_any_of_its_parents)
		{
			BOOST_CHECK_THROW(control->AppendChild(parent), std::invalid_argument);
			BOOST_CHECK_EQUAL(control->GetParent(), parent);
			BOOST_CHECK_EQUAL(parent->GetParent(), grandParent);

			BOOST_CHECK_THROW(control->AppendChild(grandParent), std::invalid_argument);
			BOOST_CHECK_EQUAL(control->GetParent(), parent);
			BOOST_CHECK(!grandParent->GetParent());
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()