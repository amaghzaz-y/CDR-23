#include <core/Actuators.h>

void Actuators::pickObject(int SIDE)
{
	if (SIDE == SIDE_A_ID)
	{
		for (uint16_t microsec = USMIN; microsec < USMAX; microsec++)
		{
			servoDriver.writeMicroseconds(SERVO_SIDE_A_L, microsec);
			servoDriver.writeMicroseconds(SERVO_SIDE_A_R, (USMAX - microsec) + 800);
		}
		side_A_full = true;
	}
	if (SIDE == SIDE_B_ID)
	{
		for (uint16_t microsec = USMIN; microsec < USMAX; microsec++)
		{
			servoDriver.writeMicroseconds(SERVO_SIDE_B_L, microsec);
			servoDriver.writeMicroseconds(SERVO_SIDE_B_R, (USMAX - microsec) + 800);
		}
		side_B_full = true;
	}
	if (SIDE == SIDE_C_ID)
	{
		for (uint16_t microsec = USMIN; microsec < USMAX; microsec++)
		{
			servoDriver.writeMicroseconds(SERVO_SIDE_C_L, microsec);
			servoDriver.writeMicroseconds(SERVO_SIDE_C_R, (USMAX - microsec) + 800);
		}
		side_C_full = true;
	}
}

void Actuators::releaseObject(int SIDE)
{
	if (SIDE == SIDE_A_ID)
	{
		for (uint16_t microsec = USMAX; microsec > USMIN; microsec--)
		{
			servoDriver.writeMicroseconds(SERVO_SIDE_A_L, microsec);
			servoDriver.writeMicroseconds(SERVO_SIDE_A_R, (USMAX - microsec) + 800);
		}
		side_A_full = false;
	}
	if (SIDE == SIDE_B_ID)
	{
		for (uint16_t microsec = USMAX; microsec > USMIN; microsec--)
		{
			servoDriver.writeMicroseconds(SERVO_SIDE_A_L, microsec);
			servoDriver.writeMicroseconds(SERVO_SIDE_A_R, (USMAX - microsec) + 800);
		}
		side_B_full = false;
	}
	if (SIDE == SIDE_C_ID)
	{
		for (uint16_t microsec = USMAX; microsec > USMIN; microsec--)
		{
			servoDriver.writeMicroseconds(SERVO_SIDE_A_L, microsec);
			servoDriver.writeMicroseconds(SERVO_SIDE_A_R, (USMAX - microsec) + 800);
		}
		side_C_full = false;
	}
}

bool Actuators::isObjectPicked(int SIDE)
{
	if (SIDE == SIDE_A_ID)
	{
		return side_A_full;
	}
	if (SIDE == SIDE_B_ID)
	{
		return side_B_full;
	}
	if (SIDE == SIDE_C_ID)
	{
		return side_C_full;
	}
	else
	{
		return true;
	}
}

void Actuators::setup()
{
	servoDriver.begin();
	servoDriver.setOscillatorFrequency(28000000);
	servoDriver.setPWMFreq(SERVO_FREQ);
	delay(50);
}

void Actuators::performTEST()
{
	pickObject(SIDE_A_ID);
	delay(5000);
	releaseObject(SIDE_A_ID);
	delay(5000);
}