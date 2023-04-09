#pragma once

class Vec2
{
private:
	float A;
	float B;

public:
	Vec2(float a, float b);
};

float cmToSteps(float distance);
float degToRad(float degrees);
float mmToSteps(float distance);
