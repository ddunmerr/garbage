#include "CShapeParser.h"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CPoint.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <sstream>

namespace
{
const std::string TRIANGLE_PREFIX = "TRIANGLE:";
const std::string RECTANGLE_PREFIX = "RECTANGLE:";
const std::string CIRCLE_PREFIX = "CIRCLE:";
const std::string LINE_PREFIX = "LINE:";

const std::string POINT_1_KEY = "P1=";
const std::string POINT_2_KEY = "P2=";
const std::string POINT_3_KEY = "P3=";
const std::string CENTER_KEY = "C=";
const std::string RADIUS_KEY = "R=";

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
	catch (const std::exception&)
	{
		return false;
	}
}
} // namespace

std::unique_ptr<IShape> CShapeParser::ParseLine(const std::string& line)
{
	std::string normalized = RemoveSpaces(line);

	if (normalized.rfind(TRIANGLE_PREFIX, 0) == 0)
	{
		CPoint p1, p2, p3;
		if (!ExtractPoint(normalized, POINT_1_KEY, p1)
			|| !ExtractPoint(normalized, POINT_2_KEY, p2)
			|| !ExtractPoint(normalized, POINT_3_KEY, p3))
		{
			return nullptr;
		}
		return std::make_unique<CTriangle>(p1, p2, p3, 0, 0);
	}

	if (normalized.rfind(RECTANGLE_PREFIX, 0) == 0)
	{
		CPoint p1, p2;
		if (!ExtractPoint(normalized, POINT_1_KEY, p1)
			|| !ExtractPoint(normalized, POINT_2_KEY, p2))
		{
			return nullptr;
		}

		double left = std::min(p1.GetX(), p2.GetX());
		double top = std::min(p1.GetY(), p2.GetY());
		double width = std::fabs(p2.GetX() - p1.GetX());
		double height = std::fabs(p2.GetY() - p1.GetY());

		return std::make_unique<CRectangle>(CPoint(left, top), width, height, 0, 0);
	}

	if (normalized.rfind(CIRCLE_PREFIX, 0) == 0)
	{
		CPoint center;
		std::string radiusStr;
		if (!ExtractPoint(normalized, CENTER_KEY, center)
			|| !ExtractValue(normalized, RADIUS_KEY, radiusStr))
		{
			return nullptr;
		}
		try
		{
			double radius = std::stod(radiusStr);
			return std::make_unique<CCircle>(center, radius, 0, 0);
		}
		catch (const std::exception&)
		{
			return nullptr;
		}
	}

	if (normalized.rfind(LINE_PREFIX, 0) == 0)
	{
		CPoint p1, p2;
		if (!ExtractPoint(normalized, POINT_1_KEY, p1)
			|| !ExtractPoint(normalized, POINT_2_KEY, p2))
		{
			return nullptr;
		}
		return std::make_unique<CLineSegment>(p1, p2, 0);
	}

	return nullptr;
}
