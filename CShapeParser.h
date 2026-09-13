#pragma once
#include "IShape.h"
#include <memory>
#include <string>

class CShapeParser
{
public:
	static std::unique_ptr<IShape> ParseLine(const std::string& line);
};
