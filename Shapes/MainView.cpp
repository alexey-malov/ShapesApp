#include "stdafx.h"
#include "MainView.h"
#include <iostream>

using namespace ui;
using namespace std;
using namespace sf;

shared_ptr<CMainView> CMainView::Create()
{
	return shared_ptr<CMainView>(new CMainView());
}

void CMainView::AddChildWithIndex(unsigned index, Vector2u const &size)
{
	auto toolbar = CToolBar::Create(size);

	InsertChildAtIndex(toolbar, index);

	m_toolbars.emplace(index, toolbar);
}

shared_ptr<CToolBar> CMainView::GetToolbar(unsigned index)
{
	return m_toolbars.at(index);
}

void CMainView::CreateMainToolbar()
{
	AddChildWithIndex(0, sf::Vector2u(490, 500));

	auto toolbar = GetToolbar(0);

	toolbar->SetRightIndentSize(float(500u - 490u));

	toolbar->AddChildWithIndex(1);
	toolbar->AddChildWithIndex(2);
	toolbar->AddChildWithIndex(3);

	auto button1 = toolbar->GetButton(1);
	auto button2 = toolbar->GetButton(2);
	auto button3 = toolbar->GetButton(3);

	button1->SetAction([]() {cout << "click" << endl; });
	button2->SetAction([]() {cout << "clack" << endl; });
	button3->SetAction([]() {cout << "bang" << endl; });

	toolbar->SetFrame({ 5, 50, 500, 50 });
	AppendChild(toolbar);
}

bool CMainView::OnWindowResized(sf::Event::SizeEvent const & event)
{
	for (auto it : m_toolbars)
	{
		it.second->SetToolbarSize({ float(event.width) 
			- it.second->GetRightIndentSize()
			, it.second->GetToolbarSize().y });
	}

	return true;
}
