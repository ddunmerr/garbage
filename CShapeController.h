#pragma once
#include "CShapeParser.h"
#include "ICanvas.h"
#include "IShape.h"
#include "consts.h"
#include <iosfwd>
#include <memory>
#include <vector>

class CShapeController
{
public:
	CShapeController(std::istream& input, std::ostream& output);

	void Run();
	void ReadShapes();
	void DrawAll(ICanvas& canvas) const;

private:
	void PrintResults() const;

	std::istream& m_input;
	std::ostream& m_output;
	std::vector<std::unique_ptr<IShape>> m_shapes;
};
