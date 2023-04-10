#pragma once
#include <types/Steps.h>
#include <types/Point2D.h>
#include <math.h>
#include <utils/utils.h>
#include <Arduino.h>

class PolarVec
{
public:
	float angle;	// in degrees;
	float distance; // in mm

	// 1.angle 2.distance
	PolarVec(float angle, float distance);
	Steps ToSteps();
	Steps ToStepsCos();
	Vec2 ToPoint2D();
	Steps RotateTo(float angle);
	Steps ToStepsCosSin();
};