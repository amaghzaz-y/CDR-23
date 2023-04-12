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
	float a1 = a - degToRad(90);
	float a2 = a + degToRad(30);
	float a3 = a + degToRad(150);
	float s1 = d * sin(a1);
	float s2 = d * sin(a2);
	float s3 = d * sin(a3);
	Steps steps(s1, -s2, s3);
	return steps;
}

Steps PolarVec::ToStepsCos()
{
	float d = mmToSteps(distance);
	float a = degToRad(angle);
	float s1 = d * cos(a - M_PI / 3);
	float s2 = d * cos(a);
	float s3 = d * cos(a + M_PI / 3);
	Serial.println(s1);
	Serial.println(s2);
	Serial.println(s3);
	Steps steps(s1, -s2, s3);
	return steps;
}
Steps PolarVec::ToStepsCosSin()
{
	float d = mmToSteps(distance);
	float a = degToRad(angle);
	float s1 = d * (sqrt(3) / 2 * cos(a) + 0.5 * sin(a));
	float s2 = d * sin(a);
	float s3 = d * (-sqrt(3) / 2 * cos(a) + 0.5 * sin(a));
	Serial.println(s1);
	Serial.println(s2);
	Serial.println(s3);
	Steps steps(s1, -s2, s3);
	return steps;
}

Vec2 PolarVec::ToPoint2D()
{
	float x = float(distance) * cos(angle);
	float y = float(distance) * sin(angle);
	Vec2 point(x, y);
	return point;
}
