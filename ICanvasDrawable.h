#pragma once
#include "ICanvas.h"
/*
Интерфейс объектов, которые могут быть
нарисованы на холсте
*/
#include "ICanvas.h"

class ICanvasDrawable
{
public:
	virtual ~ICanvasDrawable() = default;

	virtual void Draw(ICanvas& canvas) const = 0;
};
