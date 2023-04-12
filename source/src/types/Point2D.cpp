#include <types/Point2D.h>
#define UNIT 50

Point2D::Point2D(int x, int y)
{
	X = x * UNIT;
	Y = y * UNIT;
}

Point2D::Point2D()
{
	X = 0;
	Y = 0;
}

Vec2 Point2D::toPolarVec()
{
	float distance = sqrt(pow(X, 2) + pow(Y, 2));
	float angle = atan2(Y, X);
	Vec2 vec(angle, distance);
	return vec;
}

Steps Point2D::toSteps()
{
	float distance = sqrt(pow(X, 2) + pow(Y, 2));
	float angle = atan2(Y, X);
	PolarVec vec = PolarVec(angle, distance);
	Steps steps = vec.ToSteps();
	return steps;
}