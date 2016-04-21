#include "stdafx.h"
#include "Stage.h"
#include "MainView.h"

using namespace ui;
using namespace std;
using namespace sf;

CStage::CStage()
	: m_window(sf::VideoMode(500, 500), "SFML works!")
	, m_view(m_window.getDefaultView())
	, m_pRoot(ui::CBaseControl::Create())
{
	m_window.setFramerateLimit(30);
}

bool CStage::OnEvent(Event const & event)
{
	if (event.type == Event::Closed)
	{
		m_window.close();
	}
	else
	{
		m_pRoot->OnEvent(event);

		if (event.type == Event::Resized)
		{
			m_view = View(FloatRect(0.f, 0.f,
				float(m_window.getSize().x),
				float(m_window.getSize().y)));
			m_window.setView(m_view);
		}
	}
	return true;
}

void CStage::Execute()
{
	auto mainView = CMainView::Create();
	mainView->CreateMainToolbar();
	m_pRoot->AppendChild(mainView);

	while (m_window.isOpen())
	{
		Event event;
		while (m_window.pollEvent(event))
		{
			OnEvent(event);
		}

		m_window.clear();
		m_window.draw(*m_pRoot);
		m_window.display();
	}
}