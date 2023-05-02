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

// Steps Point2D::toSteps()
// {
// 	float distance = sqrt(pow(X, 2) + pow(Y, 2));
// 	float angle = 360.0 - (atan2(Y, X) * 57.2957795); // in degrees
// 	PolarVec vec = PolarVec(angle, distance);
// 	Steps steps = vec.ToSteps();
// 	return steps;
// }

// Steps Point2D::toStepsOffset(float angle, float distance)
// {
// 	float d = sqrt(pow(X, 2) + pow(Y, 2)) + distance;		// distance in mm
// 	float a = (360.0 + angle) - (atan2(Y, X) * 57.2957795); // angle in degrees
// 	//-180 < a < 180
// 	if (a > 180.0)
// 	{
// 		a -= 180.0;
// 	}
// 	else if (a < -180.0)
// 	{
// 		a += 180.0;
// 	}
// 	Serial.print("toSteps angle : ");
// 	Serial.println(a);
// 	PolarVec vec = PolarVec(a, d);
// 	Steps steps = vec.ToSteps();
// 	return steps;
// }

// float Point2D::getAngle()
// {
// 	float angle = 360.0 - atan2(Y, X) * 57.2957795; // in degrees
// 	// float angle = atan2(Y, X) * 57.2957795; // in degrees
// 	return angle;
// }