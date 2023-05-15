#include "core/Sensors.h"

void Sensors::setup()
{
	pinMode(PIN_IFM1, INPUT);
	pinMode(PIN_IFM2, INPUT);
	pinMode(PIN_IFM3, INPUT);
}

bool Sensors::getSensor(int side)
{
	if (side == SIDE_A_ID)
	{
		return digitalRead(PIN_IFM1);
	}
	else if (side == SIDE_B_ID)
	{
		return digitalRead(PIN_IFM2);
	}
	else if (side == SIDE_C_ID)
	{
		return digitalRead(PIN_IFM3);
	}
	else
	{
		return false;
	}
}