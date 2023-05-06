#include "core/Sensors.h"

void Sensors::setup()
{
	pinMode(SENSOR_A_PIN, INPUT);
	pinMode(SENSOR_B_PIN, INPUT);
	pinMode(SENSOR_C_PIN, INPUT);
}

bool Sensors::getSensor(int side)
{
	if (side == SIDE_A_ID)
	{
		return digitalRead(SENSOR_A_PIN);
	}
	else if (side == SIDE_B_ID)
	{
		return digitalRead(SENSOR_B_PIN);
	}
	else if (side == SIDE_C_ID)
	{
		return digitalRead(SENSOR_C_PIN);
	}
	else
	{
		return true;
	}
}