#include <utils/utils.h>

Vec2::Vec2(float a, float b)
{
	A = a;
	B = b;
}

float cmToSteps(float steps)
{
	return (steps * 4000) / 18.8496;
}

float degToRad(float degrees)
{
	return degrees * 0.017453292519943295769236907684886;
}
