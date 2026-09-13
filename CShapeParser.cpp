#include "CShapeParser.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CPoint.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include <cctype>
#include <sstream>

namespace
{
// Убираем все пробелы из строки для упрощения парсинга
std::string RemoveSpaces(const std::string& str)
{
	std::string result;
	result.reserve(str.size());
	for (char ch : str)
	{
		if (!std::isspace(static_cast<unsigned char>(ch)))
		{
			result += ch;
		}
	}
	return result;
}

// Ищем значение после метки вида "P1=", "C=", "R=" и т.п.
// Возвращает подстроку до следующего разделителя (; или , или конец)
bool ExtractValue(const std::string& line, const std::string& key, std::string& out)
{
	size_t pos = line.find(key);
	if (pos == std::string::npos)
	{
		return false;
	}

	size_t start = pos + key.size();
	size_t end = line.find_first_of(";,", start);
	if (end == std::string::npos)
	{
		end = line.size();
	}

	out = line.substr(start, end - start);
	return !out.empty();
}

// Извлекает точку в формате "x,y" (пробелы уже удалены)
bool ExtractPoint(const std::string& line, const std::string& key, CPoint& point)
{
	size_t pos = line.find(key);
	if (pos == std::string::npos)
	{
		return false;
	}

	size_t start = pos + key.size();
	size_t commaPos = line.find(',', start);
	if (commaPos == std::string::npos)
	{
		return false;
	}

	size_t end = line.find_first_of(";,", commaPos + 1);
	if (end == std::string::npos)
	{
		end = line.size();
	}

	try
	{
		double x = std::stod(line.substr(start, commaPos - start));
		double y = std::stod(line.substr(commaPos + 1, end - commaPos - 1));
		point = CPoint(x, y);
		return true;
	}
	catch (...)
	{
		return false;
	}
}
} // namespace

std::unique_ptr<IShape> CShapeParser::ParseLine(const std::string& line)
{
	std::string normalized = RemoveSpaces(line);

	try
	{
		if (normalized.find("TRIANGLE:") == 0)
		{
			CPoint p1, p2, p3;
			if (!ExtractPoint(normalized, "P1=", p1) || !ExtractPoint(normalized, "P2=", p2) || !ExtractPoint(normalized, "P3=", p3))
			{
				return nullptr;
			}
			return std::make_unique<CTriangle>(p1, p2, p3, 0, 0);
		}

		if (normalized.find("RECTANGLE:") == 0)
		{
			CPoint p1, p2;
			if (!ExtractPoint(normalized, "P1=", p1) || !ExtractPoint(normalized, "P2=", p2))
			{
				return nullptr;
			}
			double width = p2.GetX() - p1.GetX();
			double height = p1.GetY() - p2.GetY();
			return std::make_unique<CRectangle>(p1, width, height, 0, 0);
		}

		if (normalized.find("CIRCLE:") == 0)
		{
			CPoint center;
			std::string radiusStr;
			if (!ExtractPoint(normalized, "C=", center) || !ExtractValue(normalized, "R=", radiusStr))
			{
				return nullptr;
			}
			double radius = std::stod(radiusStr);
			return std::make_unique<CCircle>(center, radius, 0, 0);
		}

		if (normalized.find("LINE:") == 0)
		{
			CPoint p1, p2;
			if (!ExtractPoint(normalized, "P1=", p1) || !ExtractPoint(normalized, "P2=", p2))
			{
				return nullptr;
			}
			return std::make_unique<CLineSegment>(p1, p2, 0);
		}
	}
	catch (...)
	{
		return nullptr;
	}

	return nullptr;
}
