#include "CTriangle.h"
#include <cmath>
#include <iomanip>
#include <sstream>

CTriangle::CTriangle(const CPoint& vertex1, const CPoint& vertex2, const CPoint& vertex3,
	uint32_t outlineColor, uint32_t fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CTriangle::GetSideLength(const CPoint& p1, const CPoint& p2) const
{
	double dx = p2.GetX() - p1.GetX();
	double dy = p2.GetY() - p1.GetY();
	return std::sqrt(dx * dx + dy * dy);
}

double CTriangle::GetArea() const
{
	double a = GetSideLength(m_vertex1, m_vertex2);
	double b = GetSideLength(m_vertex2, m_vertex3);
	double c = GetSideLength(m_vertex3, m_vertex1);
	double p = (a + b + c) / 2.0;
	return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

double CTriangle::GetPerimeter() const
{
	return GetSideLength(m_vertex1, m_vertex2)
		+ GetSideLength(m_vertex2, m_vertex3)
		+ GetSideLength(m_vertex3, m_vertex1);
}

std::string CTriangle::ToString() const
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2)
		<< "TRIANGLE: P=" << GetPerimeter()
		<< "; S=" << GetArea();
	return oss.str();
}

uint32_t CTriangle::GetOutlineColor() const { return m_outlineColor; }
uint32_t CTriangle::GetFillColor() const { return m_fillColor; }
CPoint CTriangle::GetVertex1() const { return m_vertex1; }
CPoint CTriangle::GetVertex2() const { return m_vertex2; }
CPoint CTriangle::GetVertex3() const { return m_vertex3; }

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.FillPolygon({ m_vertex1, m_vertex2, m_vertex3 }, m_fillColor);

	canvas.DrawLine(m_vertex1, m_vertex2, m_outlineColor);
	canvas.DrawLine(m_vertex2, m_vertex3, m_outlineColor);
	canvas.DrawLine(m_vertex3, m_vertex1, m_outlineColor);
}
