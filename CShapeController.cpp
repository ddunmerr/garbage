#include "CShapeController.h"
#include "ICanvas.h"
#include "consts.h"
#include <iostream>

CShapeController::CShapeController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

void CShapeController::Run()
{
	ReadShapes();
	PrintResults();
}

void CShapeController::ReadShapes()
{
	std::string line;
	while (std::getline(m_input, line))
	{
		if (line.empty())
		{
			continue;
		}

		auto shape = CShapeParser::ParseLine(line);
		if (shape)
		{
			m_shapes.push_back(std::move(shape));
		}
		else
		{
			m_output << ERROR_UNKNOWN_COMMAND << line << std::endl;
		}
	}
}

void CShapeController::DrawAll(ICanvas& canvas) const
{
	for (const auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

void CShapeController::PrintResults() const
{
	for (const auto& shape : m_shapes)
	{
		m_output << shape->ToString() << std::endl;
	}
}
