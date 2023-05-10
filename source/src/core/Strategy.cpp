#include "Strategy.h"

void Strategy::setup()
{
	currentInstruction = 0;
	movement.setup();
	actuators.setup();
	pinMode(INIT_PIN, INPUT_PULLUP);
	pinMode(REED_PIN, INPUT_PULLUP);
	pinMode(TEAM_PIN, INPUT_PULLUP);
}

void Strategy::init()
{
	if (digitalRead(REED_PIN) == 0)
	{
		Serial.println("Starting Calibration");
		movement.calibrate();
	}
	else
	{
		Serial.println("Waiting for init...");
	}
}

void Strategy::makeSelection()
{
	if (digitalRead(TEAM_PIN) == 0)
	{
		movement.setTeam(0);
	}
	else
	{
		movement.setTeam(1);
	}
}

void Strategy::stop()
{
	Serial.println("FULL STOP IS INITIATED");
	movement.fullStop();
	Serial.println("FULL STOP HAS BEEN COMPLETE");
}

bool Strategy::isReady()
{
	if (digitalRead(REED_PIN) == 0)
	{
		Serial.println("not ready");
		return false;
	}
	Serial.println("ready");
	return true;
}

void Strategy::start(bool lidar)
{

	while (currentInstruction < arrayLength)
	{
		movement.Execute(points[currentInstruction], lidar);
		currentInstruction++;
	}
	movement.goHome();
	currentInstruction = 0;
}

void Strategy::startDebug(bool lidar)
{
	delay(2000);
	Serial.println("Starting...");
	while (currentInstruction < arrayLength)
	{
		movement.ExecuteSEMI(points[currentInstruction], lidar);
		currentInstruction++;
	}
	movement.goHomeSEMI();
	currentInstruction = 0;
}

void Strategy::startSEMI(bool lidar)
{

	while (currentInstruction < arrayLength)
	{
		if (currentInstruction == 1)
		{
			movement.setSide(SIDE_B);
		}
		if (currentInstruction == 2)
		{
			movement.setSide(SIDE_C);
		}
		movement.ExecuteSEMI(points[currentInstruction], lidar);
		// actuators.pickObject(0);
		delay(2000);
		currentInstruction++;
	}
	movement.goHomeSEMI();
	currentInstruction = 0;
}

void Strategy::startSEMIOFFSET(bool lidar)
{
	while (currentInstruction < arrayLength)
	{
		if (currentInstruction == 1)
		{
			movement.setSide(SIDE_B);
		}
		if (currentInstruction == 2)
		{
			movement.setSide(SIDE_C);
		}
		if (currentInstruction == 2)
		{
			actuators.releaseObject(0);
		}
		movement.ExecuteSEMIOFFSET(points[currentInstruction], lidar);
		if (currentInstruction == 2)
		{
			actuators.pickObject(0);
			actuators.elevateObject(SIDE_C_ID, 2);
		}
		else
		{
			delay(2000);
		}
		currentInstruction++;
	}
	movement.goHomeSEMI();
	actuators.delevateObject(SIDE_C_ID, 1);
	actuators.delevateObject(SIDE_C_ID, 0);
	actuators.releaseObject(0);
	currentInstruction = 0;
}

void Strategy::setPoints(Point2D *p, int len)
{
	points = p;
	arrayLength = len;
}

void Strategy::ready()
{
	while (!movement.isCalibrated() || !movement.atHome())
	{
		init();
	}
}