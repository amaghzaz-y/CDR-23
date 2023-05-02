#pragma once
#include <Arduino.h>
class Actuators
{
public:
	void PickObject(int SIDE);
	bool IsObjectPicked(int SIDE);
};