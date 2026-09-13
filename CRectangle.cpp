#include "CRectangle.h"
#include <iomanip>
#include <sstream>

CRectangle::CRectangle(const CPoint& leftTop, double width, double height,
	uint32_t outlineColor, uint32_t fillColor)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2.0 * (m_width + m_height);
}

std::string CRectangle::ToString() const
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2)
		<< "RECTANGLE: P=" << GetPerimeter()
		<< "; S=" << GetArea();
	return oss.str();
}

uint32_t CRectangle::GetOutlineColor() const { return m_outlineColor; }
uint32_t CRectangle::GetFillColor() const { return m_fillColor; }
CPoint CRectangle::GetLeftTop() const { return m_leftTop; }

CPoint CRectangle::GetRightBottom() const
{
	return CPoint(m_leftTop.GetX() + m_width, m_leftTop.GetY() + m_height);
}

double CRectangle::GetWidth() const { return m_width; }
double CRectangle::GetHeight() const { return m_height; }

void CRectangle::Draw(ICanvas& canvas) const
{
	std::vector<CPoint> points = {
		m_leftTop,
		CPoint(m_leftTop.GetX() + m_width, m_leftTop.GetY()),
		CPoint(m_leftTop.GetX() + m_width, m_leftTop.GetY() + m_height),
		CPoint(m_leftTop.GetX(), m_leftTop.GetY() + m_height)
	};
	canvas.FillPolygon(points, m_fillColor);
}
