#pragma once
#include "CCanvas.h"
#include "CShapeController.h"
#include <SFML/Graphics.hpp>
#include <iosfwd>

class CShapeApplication
{
public:
	CShapeApplication(std::istream& input, std::ostream& output);

	void Run();

private:
	void ProcessEvents();
	void Render();

	CShapeController m_controller;
	sf::RenderWindow m_window;
	CCanvas m_canvas;
};
