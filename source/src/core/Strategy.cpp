#include "Strategy.h"

void Strategy::setup()
{
	movement.setup();
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
	movement.fullStop();
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
	while (!movement.isCalibrated() || !movement.atHome())
	{
		init();
	}
	while (currentInstruction < arrayLength)
	{
		movement.Execute(points[currentInstruction], lidar);
		currentInstruction++;
	}
	movement.goHome();
}

void Strategy::startSEMI(bool lidar)
{
	while (!movement.isCalibrated() || !movement.atHome())
	{
		init();
	}
	while (currentInstruction < arrayLength)
	{
		movement.ExecuteSEMI(points[currentInstruction], lidar);
		currentInstruction++;
	}
	movement.goHome();
}

void Strategy::setPoints(Point2D *p, int len)
{
	points = p;
	arrayLength = len;
}