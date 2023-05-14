#include <core/Actuators.h>

void Actuators::pickObject(int SIDE)
{
	if (SIDE == SIDE_A_ID)
	{
		for (uint16_t microsec = USMIN; microsec < USMAX; microsec++)
		{
			servoDriver.writeMicroseconds(SERVO_SIDE_A_L, microsec);
			servoDriver.writeMicroseconds(SERVO_SIDE_A_R, (USMAX - microsec) + 950);
		}
		side_A_full = true;
	}
	if (SIDE == SIDE_B_ID)
	{
		for (uint16_t microsec = USMIN; microsec < (USMAX + 150); microsec++)
		{
			servoDriver.writeMicroseconds(SERVO_SIDE_B_L, microsec);
			servoDriver.writeMicroseconds(SERVO_SIDE_B_R, ((USMAX + 150) - microsec) + 720);
		}
		side_B_full = true;
	}
	if (SIDE == SIDE_C_ID)
	{
		for (uint16_t microsec = USMIN; microsec < (USMAX + 200); microsec++)
		{
			servoDriver.writeMicroseconds(SERVO_SIDE_C_L, microsec);
			servoDriver.writeMicroseconds(SERVO_SIDE_C_R, ((USMAX + 200) - microsec) + 670);
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
			servoDriver.writeMicroseconds(SERVO_SIDE_A_R, (USMAX - microsec) + 900);
		}
		side_A_full = false;
	}
	if (SIDE == SIDE_B_ID)
	{
		for (uint16_t microsec = (USMAX + 150); microsec > USMIN; microsec--)
		{
			servoDriver.writeMicroseconds(SERVO_SIDE_B_L, microsec);
			servoDriver.writeMicroseconds(SERVO_SIDE_B_R, ((USMAX + 150) - microsec) + 720);
		}
		side_B_full = false;
	}
	if (SIDE == SIDE_C_ID)
	{
		for (uint16_t microsec = (USMAX + 150); microsec > USMIN; microsec--)
		{
			servoDriver.writeMicroseconds(SERVO_SIDE_C_L, microsec);
			servoDriver.writeMicroseconds(SERVO_SIDE_C_R, ((USMAX + 150) - microsec) + 720);
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
	Serial.println();
	Serial.println("Actuators :: setting up...");
	servoDriver.begin();
	servoDriver.setOscillatorFrequency(28000000);
	servoDriver.setPWMFreq(SERVO_FREQ);
	delay(100);
	foldAll();
	delay(100);
	delevateAll();
	delay(100);
	Serial.println("Actuators :: setup done");
}

void Actuators::foldAll()
{
	Serial.println("folding");
	for (uint16_t microsec = USMIN; microsec < 2400; microsec++)
	{
		servoDriver.writeMicroseconds(SERVO_SIDE_A_L, 2300);
		servoDriver.writeMicroseconds(SERVO_SIDE_A_R, 500);
	}
	for (uint16_t microsec = USMIN; microsec < 2400; microsec++)
	{
		servoDriver.writeMicroseconds(SERVO_SIDE_B_L, 2300);
		servoDriver.writeMicroseconds(SERVO_SIDE_B_R, 475);
	}
	for (uint16_t microsec = USMIN; microsec < 2400; microsec++)
	{
		servoDriver.writeMicroseconds(SERVO_SIDE_C_L, 2300);
		servoDriver.writeMicroseconds(SERVO_SIDE_C_R, 480);
	}
}

void Actuators::defoldAll()
{
	Serial.println("defolding");
	for (uint16_t microsec = USMAX; microsec > USMIN; microsec--)
	{
		servoDriver.writeMicroseconds(SERVO_SIDE_A_L, microsec);
		servoDriver.writeMicroseconds(SERVO_SIDE_A_R, (USMAX - microsec) + 900);
	}
	for (uint16_t microsec = USMAX; microsec > USMIN; microsec--)
	{

		servoDriver.writeMicroseconds(SERVO_SIDE_B_L, microsec);
		servoDriver.writeMicroseconds(SERVO_SIDE_B_R, (USMAX - microsec) + 600);
	}
	for (uint16_t microsec = USMAX; microsec > USMIN; microsec--)
	{
		servoDriver.writeMicroseconds(SERVO_SIDE_C_L, microsec);
		servoDriver.writeMicroseconds(SERVO_SIDE_C_R, (USMAX - microsec) + 700);
	}
	Serial.println("defolded");
}

void Actuators::performTEST()
{
	while (1)
	{
		delevateObject(SIDE_A_ID, 0);
		pickObject(SIDE_A_ID);
		delay(2000);
		elevateObject(SIDE_A_ID, 0);
		delay(2000);
		elevateObject(SIDE_A_ID, 1);
		delay(2000);
		elevateObject(SIDE_A_ID, 2);
		delay(2000);
		delevateObject(SIDE_A_ID, 2);
		delay(2000);
		delevateObject(SIDE_A_ID, 1);
		delay(2000);
		delevateObject(SIDE_A_ID, 0);
		delay(2000);
		releaseObject(SIDE_A_ID);
		delay(5000);
		delevateObject(SIDE_B_ID, 0);
		pickObject(SIDE_B_ID);
		delay(2000);
		elevateObject(SIDE_B_ID, 0);
		delay(2000);
		elevateObject(SIDE_B_ID, 1);
		delay(2000);
		elevateObject(SIDE_B_ID, 2);
		delay(2000);
		delevateObject(SIDE_B_ID, 2);
		delay(2000);
		delevateObject(SIDE_B_ID, 1);
		delay(2000);
		delevateObject(SIDE_B_ID, 0);
		delay(2000);
		releaseObject(SIDE_B_ID);
		delay(5000);
		delevateObject(SIDE_C_ID, 0);
		pickObject(SIDE_C_ID);
		delay(2000);
		elevateObject(SIDE_C_ID, 0);
		delay(2000);
		elevateObject(SIDE_C_ID, 1);
		delay(2000);
		elevateObject(SIDE_C_ID, 2);
		delay(2000);
		delevateObject(SIDE_C_ID, 2);
		delay(2000);
		delevateObject(SIDE_C_ID, 1);
		delay(2000);
		delevateObject(SIDE_C_ID, 0);
		delay(2000);
		releaseObject(SIDE_C_ID);
	}
}

void Actuators::elevateObject(int SIDE, int LEVEL)
{
	if (LEVEL == 1)
	{
		if (SIDE == SIDE_A_ID)
		{
			for (uint16_t microsec = US_LEVEL_0; microsec < US_LEVEL_1; microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_A_U, microsec);
			}
		}
		else if (SIDE == SIDE_B_ID)
		{
			for (uint16_t microsec = US_LEVEL_0; microsec < (US_LEVEL_1 + 150); microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_B_U, microsec);
			}
		}
		else if (SIDE == SIDE_C_ID)
		{
			for (uint16_t microsec = US_LEVEL_0; microsec < US_LEVEL_1; microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_C_U, microsec);
			}
		}
	}
	else if (LEVEL == 2)
	{
		if (SIDE == SIDE_A_ID)
		{
			for (uint16_t microsec = US_LEVEL_1; microsec < US_LEVEL_2; microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_A_U, microsec);
			}
		}
		else if (SIDE == SIDE_B_ID)
		{
			for (uint16_t microsec = (US_LEVEL_1 + 150); microsec < (US_LEVEL_2 + 250); microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_B_U, microsec);
			}
		}
		else if (SIDE == SIDE_C_ID)
		{
			for (uint16_t microsec = US_LEVEL_1; microsec < US_LEVEL_2; microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_C_U, microsec);
			}
		}
	}
	else if (LEVEL == 3)
	{
		if (SIDE == SIDE_A_ID)
		{
			for (uint16_t microsec = US_LEVEL_2; microsec < US_LEVEL_3; microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_A_U, microsec);
			}
		}
		else if (SIDE == SIDE_B_ID)
		{
			for (uint16_t microsec = (US_LEVEL_2 + 250); microsec < (US_LEVEL_3 + 250); microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_B_U, microsec);
			}
		}
		else if (SIDE == SIDE_C_ID)
		{
			for (uint16_t microsec = US_LEVEL_2; microsec < US_LEVEL_3; microsec++)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_C_U, microsec);
			}
		}
	}
}

void Actuators::delevateObject(int SIDE, int LEVEL)
{
	if (LEVEL == 0)
	{
		if (SIDE == SIDE_A_ID)
		{
			for (uint16_t microsec = US_LEVEL_1; microsec > US_LEVEL_0; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_A_U, microsec);
			}
		}
		else if (SIDE == SIDE_B_ID)
		{
			for (uint16_t microsec = US_LEVEL_1; microsec > US_LEVEL_0; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_B_U, microsec);
			}
		}
		else if (SIDE == SIDE_C_ID)
		{
			for (uint16_t microsec = US_LEVEL_1; microsec > US_LEVEL_0; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_C_U, microsec);
			}
		}
	}
	else if (LEVEL == 1)
	{
		if (SIDE == SIDE_A_ID)
		{
			for (uint16_t microsec = US_LEVEL_2; microsec > US_LEVEL_1; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_A_U, microsec);
			}
		}
		else if (SIDE == SIDE_B_ID)
		{
			for (uint16_t microsec = US_LEVEL_2; microsec > US_LEVEL_1; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_B_U, microsec);
			}
		}
		else if (SIDE == SIDE_C_ID)
		{
			for (uint16_t microsec = US_LEVEL_2; microsec > US_LEVEL_1; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_C_U, microsec);
			}
		}
	}
	else if (LEVEL == 2)
	{
		if (SIDE == SIDE_A_ID)
		{
			for (uint16_t microsec = US_LEVEL_3; microsec > US_LEVEL_2; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_A_U, microsec);
			}
		}
		else if (SIDE == SIDE_B_ID)
		{
			for (uint16_t microsec = US_LEVEL_3; microsec > US_LEVEL_2; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_B_U, microsec);
			}
		}
		else if (SIDE == SIDE_C_ID)
		{
			for (uint16_t microsec = US_LEVEL_3; microsec > US_LEVEL_2; microsec--)
			{
				servoDriver.writeMicroseconds(SERVO_SIDE_C_U, microsec);
			}
		}
	}
}

void Actuators::setToZero()
{
	servoDriver.writeMicroseconds(0, 200);
	servoDriver.writeMicroseconds(1, 2400);
	servoDriver.writeMicroseconds(2, 2400);
	servoDriver.writeMicroseconds(3, 200);
	servoDriver.writeMicroseconds(4, 200);
	servoDriver.writeMicroseconds(5, 2400);
};

void Actuators::delevateAll()
{
	delevateObject(SIDE_A_ID, 0);
	delevateObject(SIDE_B_ID, 0);
	delevateObject(SIDE_C_ID, 0);
}