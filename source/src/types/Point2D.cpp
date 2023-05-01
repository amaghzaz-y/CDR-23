#include <types/Point2D.h>
#define UNIT 1

Point2D::Point2D(int x, int y)
{
	X = x;
	Y = y;
}

Point2D::Point2D()
{
	X = 0;
	Y = 0;
}

Steps Point2D::toSteps()
{
	float distance = sqrt(pow(X, 2) + pow(Y, 2));
	float angle = 360.0 - atan2(Y, X) * 57.2957795; // in degrees
	PolarVec vec = PolarVec(angle, distance);
	Steps steps = vec.ToSteps();
	return steps;
}

Steps Point2D::toStepsOffset(float angle, float distance)
{
	float distance = sqrt(pow(X, 2) + pow(Y, 2)) + distance;
	float angle = 360.0 - angle - atan2(Y, X) * 57.2957795; // in degrees
	PolarVec vec = PolarVec(angle, distance);
	Steps steps = vec.ToSteps();
	return steps;
}

float Point2D::getAngle()
{
	float angle = 360.0 - atan2(Y, X) * 57.2957795; // in degrees
	return angle;
}