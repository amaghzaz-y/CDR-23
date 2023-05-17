#include "Strategy.h"

void Strategy::setup()
{
	currentInstruction = 0;
	movement.setup();
	actuators.setup();
	pinMode(INIT_PIN, INPUT_PULLUP);
	pinMode(TEAM_PIN, INPUT);
	pinMode(REED_PIN, INPUT_PULLUP);
	pinMode(PIN_L4, INPUT_PULLUP);
}

void Strategy::init()
{
	if (digitalRead(INIT_PIN) == 0)
	{
		Serial.println("Starting Calibration");
		movement.Calibrate();
	}
	else
	{
		Serial.println("Waiting for init...");
	}
}

void Strategy::teamSelection()
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

void Strategy::testINPUT()
{
	Serial.print("L1 : ");
	Serial.print(digitalRead(PIN_L1));
	Serial.print("   L2 : ");
	Serial.print(digitalRead(PIN_L2));
	Serial.print("   L3 : ");
	Serial.print(digitalRead(PIN_L3));
	Serial.print("   L4 : ");
	Serial.println(digitalRead(PIN_L4));
}

void Strategy::stop()
{
	Serial.println("FULL STOP IS INITIATED");
	movement.FullStop();
	Serial.println("FULL STOP HAS BEEN COMPLETE");
}

void Strategy::Ready()
{
	while (digitalRead(REED_PIN) == 1)
	{
		Serial.println("not ready");
	}
	Serial.println("ready");
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
	delay(1600);
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
		delay(1600);
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
			delay(1600);
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

void Strategy::Initiation()
{
	while (!movement.isCalibrated() || !movement.atHome())
	{
		init();
		teamSelection();
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
	Point2D delta0 = Point2D(PolarVec(0, 160).toVec2().A + zoneCenter.X, PolarVec(0, 160).toVec2().B + zoneCenter.Y);
	Point2D delta1 = Point2D(PolarVec(90, 160).toVec2().A + zoneCenter.X, PolarVec(90, 160).toVec2().B + zoneCenter.Y);
	Point2D delta2 = Point2D(PolarVec(-180, 160).toVec2().A + zoneCenter.X, PolarVec(-180, 160).toVec2().B + zoneCenter.Y);
	// Dropping first brown part, IMPORTANT side A facing north !!!
	movement.setCurrentPosition(entryPoint);
	// ----------------------------------
	// making the first cake @ delta0 //
	// ----------------------------------
	movement.setSide(SIDE_C);
	actuators.elevateObject(SIDE_C_ID, 2);
	movement.ExecuteSEMIOFFSET(delta0, lidar);
	actuators.delevateObject(SIDE_C_ID, 0);
	actuators.releaseObject(SIDE_C_ID);
	// picking rest brown parts
	actuators.elevateObject(SIDE_C_ID, 1);
	actuators.pickObject(SIDE_C_ID);
	// Return to center
	movement.setSide(SIDE_AB);
	movement.ExecuteSEMI(zoneCenter, lidar);
	// dropping first yellow part
	actuators.elevateObject(SIDE_B_ID, 3);
	movement.setSide(SIDE_B);
	movement.ExecuteSEMI(delta0, lidar);
	actuators.delevateObject(SIDE_B_ID, 1);
	actuators.releaseObject(SIDE_B_ID);
	// picking rest yellow parts
	actuators.elevateObject(SIDE_B_ID, 2);
	actuators.pickObject(SIDE_B_ID);
	// Return to center
	movement.setSide(SIDE_CA);
	movement.ExecuteSEMI(zoneCenter, lidar);
	// dropping first pink part
	actuators.elevateObject(SIDE_A_ID, 3);
	movement.setSide(SIDE_A);
	movement.ExecuteSEMI(delta0, lidar);
	actuators.delevateObject(SIDE_A_ID, 2);
	actuators.releaseObject(SIDE_A_ID);
	// picking rest pink parts	// Return to center
	actuators.elevateObject(SIDE_A_ID, 3);
	actuators.pickObject(SIDE_A_ID);
	// Return to center
	movement.setSide(SIDE_BC);
	movement.ExecuteSEMIOFFSET(zoneCenter, lidar);
	// ----------------------------------
	// making the second cake @ delta1 //
	// ----------------------------------
	movement.setSide(SIDE_C);
	actuators.elevateObject(SIDE_C_ID, 2);
	movement.ExecuteSEMI(delta1, lidar);
	// drop the second brown cake
	actuators.delevateObject(SIDE_C_ID, 0);
	actuators.releaseObject(SIDE_C_ID);
	// pickup the rest
	actuators.elevateObject(SIDE_C_ID, 1);
	actuators.pickObject(SIDE_C_ID);
	// return to center
	movement.setSide(SIDE_AB);
	movement.ExecuteSEMIOFFSET(zoneCenter, lidar);
	// drop the yellow cake
	actuators.elevateObject(SIDE_B_ID, 3);
	movement.setSide(SIDE_B);
	movement.ExecuteSEMI(delta1, lidar);
	actuators.delevateObject(SIDE_B_ID, 1);
	actuators.releaseObject(SIDE_B_ID);
	// pick the rest
	actuators.elevateObject(SIDE_B_ID, 2);
	actuators.pickObject(SIDE_B_ID);
	// return to center
	movement.setSide(SIDE_CA);
	movement.ExecuteSEMI(zoneCenter, lidar);
	// drop the pink cake
	actuators.elevateObject(SIDE_A_ID, 3);
	movement.setSide(SIDE_A);
	movement.ExecuteSEMI(delta1, lidar);
	actuators.delevateObject(SIDE_A_ID, 2);
	actuators.releaseObject(SIDE_A_ID);
	actuators.elevateObject(SIDE_A_ID, 3);
	actuators.pickObject(SIDE_A_ID);
	// return to center
	movement.setSide(SIDE_BC);
	movement.ExecuteSEMI(zoneCenter, lidar);
	// ----------------------------------
	// making the third cake @ delta2 //
	// ----------------------------------
	// putting the third brown cake
	movement.setSide(SIDE_C);
	movement.ExecuteSEMI(delta2, lidar);
	actuators.delevateObject(SIDE_C_ID, 0);
	actuators.releaseObject(SIDE_C_ID);
	// return to center
	movement.setSide(SIDE_AB);
	movement.ExecuteSEMI(zoneCenter, lidar);
	// drop the third yellow cake
	movement.setSide(SIDE_B);
	actuators.elevateObject(SIDE_B_ID, 2);
	movement.ExecuteSEMI(delta2, lidar);
	actuators.delevateObject(SIDE_B_ID, 1);
	actuators.releaseObject(SIDE_B_ID);
	// return to center
	movement.setSide(SIDE_CA);
	movement.ExecuteSEMI(zoneCenter, lidar);
	// dropping the last pink cake
	movement.setSide(SIDE_A);
	actuators.elevateObject(SIDE_A_ID, 3);
	movement.ExecuteSEMI(delta2, lidar);
	actuators.delevateObject(SIDE_A_ID, 2);
	actuators.releaseObject(SIDE_A_ID);
	actuators.elevateObject(SIDE_A_ID, 3);
	// return to center
	movement.setSide(SIDE_BC);
	movement.ExecuteSEMI(zoneCenter, lidar);
}

void Strategy::Homologuation(bool lidar)
{
	Initiation();
	Ready();
	cookMeth(lidar);
}

Point2D Strategy::getCurrentPoint()
{
	return movement.getCurrentPoint();
}