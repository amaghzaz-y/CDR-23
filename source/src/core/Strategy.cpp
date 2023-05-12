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
		movement.Calibrate();
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
	movement.FullStop();
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

void Strategy::startStratA(bool lidar)
{
	actuators.foldAll();
	actuators.delevateObject(SIDE_A_ID, 0);
	actuators.releaseObject(SIDE_A_ID);
	movement.ExecuteSEMIOFFSET(Point2D(575, 225), lidar);
	actuators.pickObject(SIDE_A_ID);
	actuators.elevateObject(SIDE_A, 1);

	movement.setSide(SIDE_B);
	actuators.delevateObject(SIDE_B_ID, 0);
	actuators.releaseObject(SIDE_B_ID);
	movement.ExecuteSEMIOFFSET(Point2D(775, 225), lidar);
	actuators.pickObject(SIDE_B_ID);
	actuators.elevateObject(SIDE_B_ID, 1);

	movement.setSide(SIDE_C);
	actuators.delevateObject(SIDE_C_ID, 0);
	actuators.releaseObject(SIDE_C_ID);
	movement.ExecuteSEMIOFFSET(Point2D(1125, 725), lidar);
	actuators.pickObject(SIDE_C_ID);
	actuators.elevateObject(SIDE_C_ID, 1);

	movement.ExecuteSEMI(Point2D(1125, 1775), lidar);
	actuators.delevateObject(SIDE_A_ID, 0);
	actuators.delevateObject(SIDE_B_ID, 0);
	actuators.delevateObject(SIDE_C_ID, 0);
	actuators.releaseObject(SIDE_A_ID);
	actuators.releaseObject(SIDE_B_ID);
	actuators.releaseObject(SIDE_C_ID);
	movement.FullStop();
}

void Strategy::cookMeth(bool lidar)
{
	// Points of interest
	Point2D entryPoint = Point2D(0, 0);
	Point2D zoneCenter = Point2D(500, 0);
	Point2D delta0 = Point2D(PolarVec(0, 285).toVec2().A + zoneCenter.X, PolarVec(0, 285).toVec2().B + zoneCenter.Y);
	Point2D delta1 = Point2D(PolarVec(-90, 285).toVec2().A + zoneCenter.X, PolarVec(-90, 285).toVec2().B + zoneCenter.Y);
	Point2D delta2 = Point2D(PolarVec(-180, 285).toVec2().A + zoneCenter.X, PolarVec(-180, 285).toVec2().B + zoneCenter.Y);
	// Dropping first brown part, IMPORTANT side A facing north !!!
	movement.setCurrentPosition(entryPoint);
	//
	movement.setSide(SIDE_C);
	movement.ExecuteSEMI(delta0, lidar);
	actuators.delevateObject(SIDE_C_ID, 0);
	actuators.releaseObject(SIDE_C_ID);
	// picking rest brown parts
	actuators.elevateObject(SIDE_C_ID, 1);
	actuators.pickObject(SIDE_C_ID);
	// Return to center
	movement.setSide(SIDE_AB);
	movement.ExecuteSEMI(zoneCenter, lidar);
	// dropping first yellow part
	actuators.elevateObject(SIDE_B_ID, 1);
	movement.setSide(SIDE_B);
	movement.ExecuteSEMI(delta0, lidar);
	actuators.releaseObject(SIDE_B_ID);
	// picking rest yellow parts
	actuators.elevateObject(SIDE_B_ID, 2);
	actuators.pickObject(SIDE_B_ID);
	// Return to center
	movement.setSide(SIDE_CA);
	movement.ExecuteSEMI(zoneCenter, lidar);
	// dropping first pink part
	actuators.elevateObject(SIDE_A_ID, 2);
	movement.setSide(SIDE_A);
	movement.ExecuteSEMI(delta0, lidar);
	actuators.releaseObject(SIDE_A_ID);
	// picking rest pink parts	// Return to center
	movement.ExecuteSEMI(zoneCenter, lidar);
	actuators.elevateObject(SIDE_A_ID, 3);
	actuators.pickObject(SIDE_A_ID);
	// Return to center
	movement.setSide(SIDE_BC);
	movement.ExecuteSEMI(zoneCenter, lidar);
}