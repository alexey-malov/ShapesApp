#include "stdafx.h"
#include "Stage.h"

using namespace ui;
using namespace std;
using namespace sf;

CStage::CStage(std::unique_ptr<sf::RenderWindow> && window)
	: m_window(move(window))
	, m_view(m_window->getDefaultView())
	, m_root(ui::CBaseControl::Create())
{
	m_window->setFramerateLimit(30);
}

bool CStage::OnEvent(Event const & event)
{
	if (event.type == Event::Closed)
	{
		m_window->close();
	}
	else
	{
		m_root->OnEvent(event);

		if (event.type == Event::Resized)
		{
			m_view = View(FloatRect(0.f, 0.f,
				float(m_window->getSize().x),
				float(m_window->getSize().y)));
			m_window->setView(m_view);
		}
	}
	return true;
}

void CStage::Execute()
{
	while (m_window->isOpen())
	{
		Event event;
		while (m_window->pollEvent(event))
		{
			OnEvent(event);
		}
		m_window->clear();
		m_window->draw(*m_root);
		m_window->display();
	}
}

CBaseControlPtr ui::CStage::GetRoot() const
{
	return m_root;
}
