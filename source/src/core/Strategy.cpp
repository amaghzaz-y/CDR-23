#include "Strategy.h"

Strategy::Strategy()
{
}

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
	if (!movement.isCalibrated() || !movement.atHome())
	{
		init();
	}
	movement.start(lidar);
}
