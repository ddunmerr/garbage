#include "stdafx.h"
#include "CCanvas.h"
#include "CShapeApplication.h"
#include "CShapeController.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	CShapeApplication app(std::cin, std::cout);
	app.Run();
	return 0;
}
