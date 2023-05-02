#include <types/PolarVec.h>

PolarVec::PolarVec(float a, float d)
{
	angle = a;
	distance = d;
};

Steps PolarVec::ToSteps()
{
	float d = mmToSteps(distance);
	float a = degToRad(angle);
	float s1 = d * (sqrt(3) / 2 * cos(a) + 0.5 * sin(a));
	float s2 = d * sin(a);
	float s3 = d * (-sqrt(3) / 2 * cos(a) + 0.5 * sin(a));
	Steps steps(s1, -s2, s3);
	return steps;
}
