#pragma once
#include <types/Steps.h>
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
};