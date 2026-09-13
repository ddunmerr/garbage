#include "CCanvas.h"
#include <array>

namespace
{
sf::Color ToSfColor(uint32_t color)
{
	return sf::Color(
		static_cast<std::uint8_t>((color >> 16) & 0xFF),
		static_cast<std::uint8_t>((color >> 8) & 0xFF),
		static_cast<std::uint8_t>(color & 0xFF));
}
} // namespace

CCanvas::CCanvas(sf::RenderTarget& target)
	: m_target(target)
{
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor) const
{
	std::array<sf::Vertex, 2> line = {
		sf::Vertex{ sf::Vector2f(static_cast<float>(from.GetX()), static_cast<float>(from.GetY())), ToSfColor(lineColor) },
		sf::Vertex{ sf::Vector2f(static_cast<float>(to.GetX()), static_cast<float>(to.GetY())), ToSfColor(lineColor) }
	};
	m_target.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
}

void CCanvas::FillPolygon(std::vector<CPoint> points, uint32_t fillColor) const
{
	sf::ConvexShape polygon;
	polygon.setPointCount(points.size());
	for (size_t i = 0; i < points.size(); ++i)
	{
		polygon.setPoint(i, sf::Vector2f(static_cast<float>(points[i].GetX()), static_cast<float>(points[i].GetY())));
	}
	polygon.setFillColor(ToSfColor(fillColor));
	m_target.draw(polygon);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor) const
{
	sf::CircleShape circle(static_cast<float>(radius));
	circle.setOrigin({ static_cast<float>(radius), static_cast<float>(radius) });
	circle.setPosition({ static_cast<float>(center.GetX()), static_cast<float>(center.GetY()) });
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(1.0f);
	circle.setOutlineColor(ToSfColor(lineColor));
	m_target.draw(circle);
}

void CCanvas::FillCircle(CPoint center, double radius, uint32_t fillColor) const
{
	sf::CircleShape circle(static_cast<float>(radius));
	circle.setOrigin({ static_cast<float>(radius), static_cast<float>(radius) });
	circle.setPosition({ static_cast<float>(center.GetX()), static_cast<float>(center.GetY()) });
	circle.setFillColor(ToSfColor(fillColor));
	m_target.draw(circle);
}
