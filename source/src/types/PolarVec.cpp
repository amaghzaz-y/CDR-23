#include <types/PolarVec.h>

PolarVec::PolarVec(float a, float d)
{
	angle = degToRad(a);
	distance = mmToSteps(d);
};

Steps PolarVec::ToSteps()
{

	float s1 = distance * (sqrt(3) / 2 * cos(angle) + 0.5 * sin(angle));
	float s2 = distance * sin(angle);
	float s3 = distance * (-sqrt(3) / 2 * cos(angle) + 0.5 * sin(angle));
	Steps steps(s1, -s2, s3);
	return steps;
}

Vec2 PolarVec::toVec2()
{
	float x = distance * cos(angle);
	float y = distance * sin(angle);
	return Vec2(x, y);
};
