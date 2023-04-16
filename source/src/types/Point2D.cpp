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
	float angle = 360.0 - atan2(Y, X) * 57.2957795;
	Serial.print(" ### Distance : ");
	Serial.print(distance);
	Serial.print("Angle : ");
	Serial.print(angle);
	Serial.println(" ###");
	PolarVec vec = PolarVec(angle, distance);
	Steps steps = vec.ToStepsCosSin();
	return steps;
}