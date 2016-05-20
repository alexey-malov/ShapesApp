#include "stdafx.h"
#include "..\BaseControl.h"

using namespace ui;
using namespace std;

using boost::algorithm::all_of;
using sf::Vector2f;
using sf::FloatRect;

class CMockControl : public CBaseControl
{
public:
	size_t removedFromParentCounter = 0;
	size_t addedToParentCounter = 0;

	static std::shared_ptr<CMockControl> Create()
	{
		return std::make_shared<CMockControl>();
	}

	void OnAddedToParent() override
	{
		addedToParentCounter++;
	}

	void OnRemovedFromParent() override
	{
		removedFromParentCounter++;
	}
};

typedef shared_ptr<CMockControl> CMockControlPtr;

struct BaseControl_
{
	CMockControlPtr control = CMockControl::Create();
	CMockControlPtr parent = CMockControl::Create();
	CMockControlPtr grandParent = CMockControl::Create();
	const vector<CMockControlPtr> children = { CMockControl::Create(), CMockControl::Create(), CMockControl::Create(), CMockControl::Create()};

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
		BOOST_AUTO_TEST_CASE(transforms_coordinates_using_own_frame)
		{
			const Vector2f pt(3.45f, 5.17f);
			const FloatRect frm(2.17f, 16.23f, 15.29f, 17.98f);

			control->SetFrame(frm);

			const auto origin = Vector2f(frm.left, frm.top);

			BOOST_CHECK(control->LocalToGlobal(pt) == (pt + origin));
			BOOST_CHECK(control->GlobalToLocal(pt) == (pt - origin));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(has_origin_equal_to_frame_left_top_corner)
	{
		const FloatRect frm(2.17f, 16.23f, 15.29f, 17.98f);
		const auto origin = Vector2f(frm.left, frm.top);
		control->SetFrame(frm);
		BOOST_CHECK(origin == control->GetOrigin());
	}

	BOOST_AUTO_TEST_CASE(can_perform_point_hit_test)
	{
		const FloatRect frm(-4, 3, 8, 5);
		const Vector2f size(frm.width, frm.height);
		const Vector2f eps(frm.width * 0.1f, frm.height * 0.1f);
		
		control->SetFrame(frm);
		BOOST_CHECK(control->HitTest({ 0, 0 }));
		BOOST_CHECK(!control->HitTest(Vector2f() - eps));
		BOOST_CHECK(!control->HitTest({ frm.width, frm.height }));
		BOOST_CHECK(control->HitTest(size - eps));
	}

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

			control->SetFrame({ 2.13f, 2.35f, 0.32f, 9.77f });
			parent->SetFrame({ 7.16f, 8.33f, 7.11f, 8.64f });
			grandParent->SetFrame({ 8.11f, -7.16f, 3.08f, 1.1f });
		}
	};
	BOOST_FIXTURE_TEST_SUITE(being_a_child, being_a_child_)
		BOOST_AUTO_TEST_CASE(can_be_removed_from_parent)
		{
			control->RemoveFromParent();
			BOOST_CHECK(!control->GetParent());
			BOOST_CHECK_EQUAL(parent->GetChildCount(), 0u);
		}
		BOOST_AUTO_TEST_CASE(receives_notifications_when_removed_from_parent)
		{
			auto oldCounter = control->removedFromParentCounter;
			control->RemoveFromParent();
			BOOST_CHECK_EQUAL(control->removedFromParentCounter, oldCounter + 1);
			control->RemoveFromParent();
			BOOST_CHECK_EQUAL(control->removedFromParentCounter, oldCounter + 1);
			parent->AppendChild(control);
			control->RemoveFromParent();
			BOOST_CHECK_EQUAL(control->removedFromParentCounter, oldCounter + 2);
		}
		BOOST_AUTO_TEST_CASE(receives_notifications_when_added_to_parent)
		{
			BOOST_CHECK_EQUAL(control->addedToParentCounter, 1);
			control->RemoveFromParent();
			parent->AppendChild(control);
			BOOST_CHECK_EQUAL(control->addedToParentCounter, 2);
			parent->InsertChildAtIndex(control, 2);
			BOOST_CHECK_EQUAL(control->addedToParentCounter, 2);
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
		BOOST_AUTO_TEST_CASE(takes_all_parent_frames_into_account)
		{
			const Vector2f pt(19.17f, 7.33f);
			BOOST_CHECK(control->LocalToGlobal(pt) == pt + (control->GetOrigin() + parent->GetOrigin() + grandParent->GetOrigin()));
			BOOST_CHECK(control->GlobalToLocal(pt) == pt - (control->GetOrigin() + parent->GetOrigin() + grandParent->GetOrigin()));
		}
		BOOST_AUTO_TEST_CASE(can_convert_point_from_and_to_other_controls_coordinate_frame)
		{
			const auto otherControl = CBaseControl::Create();
			otherControl->SetFrame({ 1.f, 2.f, 3.f, 4.f });
			grandParent->AppendChild(otherControl);

			const Vector2f pt(19.17f, 7.33f);
			BOOST_CHECK(control->ConvertPointFromControl(pt, otherControl) == 
				control->GlobalToLocal(otherControl->LocalToGlobal(pt))
			);

			BOOST_CHECK(control->ConvertPointToControl(pt, otherControl) ==
				otherControl->GlobalToLocal(control->LocalToGlobal(pt))
			);
		}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(pending_addition_of_children)
		class test_heir_CBaseControl_ : public CBaseControl
		{
		};

		struct wrap_test_heir_to_unique_ptr_ : BaseControl_
		{
			unique_ptr<test_heir_CBaseControl_> unqPtr = make_unique<test_heir_CBaseControl_>();
		};
		BOOST_FIXTURE_TEST_SUITE(after_wrap_test_heir_to_unique_ptr, wrap_test_heir_to_unique_ptr_)
			BOOST_AUTO_TEST_CASE(has_no_childrens)
			{
				BOOST_CHECK_EQUAL(unqPtr->GetChildCount(), 0);
			}
		BOOST_AUTO_TEST_SUITE_END()

		struct can_append_child_and_dont_get_except_
			: public wrap_test_heir_to_unique_ptr_
		{
			can_append_child_and_dont_get_except_()
			{
				BOOST_REQUIRE_NO_THROW(unqPtr->AppendChild(children[0]));
			}
		};
		BOOST_FIXTURE_TEST_SUITE(can_append_child_and_dont_get_except, can_append_child_and_dont_get_except_)
			BOOST_AUTO_TEST_CASE(has_a_one_children)
			{
				BOOST_CHECK_EQUAL(unqPtr->GetChildCount(), 1);
			}
			BOOST_AUTO_TEST_CASE(can_get_a_children_by_index)
			{
				BOOST_CHECK_EQUAL(unqPtr->GetChild(0), children[0]);
			}
			BOOST_AUTO_TEST_CASE(childrens_parent_is_equal_nullptr)
			{
				BOOST_CHECK(children[0]->GetParent() == nullptr);
			}
			BOOST_AUTO_TEST_CASE(if_child_has_a_parent_then_after_append_to_new_node_his_parent_is_equal_nullptr)
			{
				auto oldParent = CBaseControl::Create();
				oldParent->AppendChild(children[1]);
				BOOST_CHECK(children[1]->GetParent() == oldParent);

				BOOST_CHECK_NO_THROW(unqPtr->AppendChild(children[1]));
				BOOST_CHECK_EQUAL(unqPtr->GetChildCount(), 2);
				BOOST_CHECK(unqPtr->GetChild(1) == children[1]);
				BOOST_CHECK(unqPtr->GetChild(1)->GetParent() == nullptr);
			}
		BOOST_AUTO_TEST_SUITE_END()

		struct after_convert_from_unique_to_shared_ptr_ : can_append_child_and_dont_get_except_
		{
			after_convert_from_unique_to_shared_ptr_()
			{
				BOOST_REQUIRE_NO_THROW(shrdPtr->AppendChild(children[1]));
			}

			shared_ptr<test_heir_CBaseControl_> shrdPtr = move(unqPtr);
		};
		BOOST_FIXTURE_TEST_SUITE(after_convert_from_unique_to_shared_ptr, after_convert_from_unique_to_shared_ptr_)
			BOOST_AUTO_TEST_CASE(childrens_parent_is_not_equal_a_nullptr)
			{
				BOOST_CHECK_EQUAL(children[0]->GetParent(), shrdPtr);
			}
		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()