#pragma once
#include <math.h>
#include <utils/utils.h>
#include <types/Steps.h>
#include <types/PolarVec.h>

class Point2D
{
public:
	int X;
	int Y;
	Point2D(int x, int y);
	Vec2 toPolarVec();
	Steps toSteps();
};
