#include "CShapeApplication.h"

CShapeApplication::CShapeApplication(std::istream& input, std::ostream& output)
	: m_controller(input, output)
	, m_window(sf::VideoMode({ 1280, 720 }), "Shapes")
	, m_canvas(m_window)
{
}

void CShapeApplication::Run()
{
	m_controller.Run();
	while (m_window.isOpen())
	{
		ProcessEvents();
		Render();
	}
}

void CShapeApplication::ProcessEvents()
{
	while (const std::optional event = m_window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			m_window.close();
		}
	}
}

void CShapeApplication::Render()
{
	m_window.clear(sf::Color::White);
	m_controller.DrawAll(m_canvas);
	m_window.display();
}
