#include <types/Steps.h>
#include <types/Point2D.h>
#include <math.h>
#include <utils/utils.h>

class PolarVec
{
public:
	float angle;
	float distance;
	PolarVec(float angle, float distance);
	Steps ToSteps();
	Vec2 ToPoint2D();
};