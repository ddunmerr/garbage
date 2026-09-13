/*
Конкретный класс холста, реализующий
перечисленные операции рисования с
использованием некоторого графического API,
предоставляемого операционной системой либо
сторонней библиотекой
*/

#pragma once
#include "ICanvas.h"
#include <SFML/Graphics.hpp>

class CCanvas : public ICanvas
{
public:
	CCanvas(sf::RenderTarget& target);

	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) const override;
	void FillPolygon(std::vector<CPoint> points, uint32_t fillColor) const override;
	void DrawCircle(CPoint center, double radius, uint32_t lineColor) const override;
	void FillCircle(CPoint center, double radius, uint32_t fillColor) const override;

private:
	sf::RenderTarget& m_target;
};
