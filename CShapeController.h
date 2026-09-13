#pragma once
#include "CShapeParser.h"
#include "IShape.h"
#include <iosfwd>
#include <memory>
#include <vector>

class ICanvas;

class CShapeController
{
public:
	CShapeController(std::istream& input, std::ostream& output);

	void Run();
	void DrawAll(ICanvas& canvas) const;

private:
	void ReadShapes();
	void PrintResults() const;

	std::istream& m_input;
	std::ostream& m_output;
	std::vector<std::unique_ptr<IShape>> m_shapes;
};
