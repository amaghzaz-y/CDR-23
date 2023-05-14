#include <Arduino.h>
#include <types/PolarVec.h>
#include <core/Lidar.h>
#include <core/Strategy.h>
#include <lib/ticker/Ticker.h>
#include <utils/utils.h>
#include <core/Actuators.h>
void log(char *msg, int value)
{
	Serial.print(msg);
	Serial.print(" : ");
	Serial.println(value);
}

// Movement movement;
Strategy strategy;
Lidar lidar;
// Actuators actuators;

void FullStop()
{
	// strategy.stop();
}

Ticker ticker(FullStop,
			  100000, 0, MILLIS);

Point2D points[] = {Point2D(1000, 500), Point2D(1000, 1000), Point2D(700, 1000)};

void LidarTask(void *pvParameters)
{
	for (;;)
	{
		lidar.Task();
		// ticker.update();
	}
}

void setup()
{
	Serial.begin(115200);
	// lidar.setup();
	// lidar.setAngle(180);
	// lidar.setRadius(360);
	// lidar.setMaxRange(350);
	// ticker.start();
	strategy.setup();
	// actuators.setup();
	// movement.setup();
	delay(5000);

	// xTaskCreatePinnedToCore(LidarTask, "lidarTask", 10000, NULL, 0, NULL, 0);
	// strategy.setPoints(points, 3);
}

void loop()
{
	// Serial.print("LIDAR ANGLE :: ");
	// Serial.print(lidar.scan().A);
	// Serial.print("  DISTAMCE :: ");
	// Serial.println(lidar.scan().B);
	strategy.actuators.initCook();
	strategy.cookMeth(false);
	strategy.actuators.normalize();
	while (1)
		;
	// strategy.actuators.performTEST();
	// strategy.actuators.elevateObject(SIDE_A_ID, 1);
	// delay(2000);
	// strategy.actuators.elevateObject(SIDE_A_ID, 2);
	// delay(2000);
	// strategy.actuators.elevateObject(SIDE_A_ID, 3);
	// delay(2000);
	// strategy.actuators.delevateObject(SIDE_A_ID, 2);
	// delay(2000);
	// strategy.actuators.delevateObject(SIDE_A_ID, 1);
	// delay(2000);
	// strategy.actuators.delevateObject(SIDE_A_ID, 0);
	// delay(2000);
	// actuators.performTEST();
	// movement.Calibrate();
	// actuators.delevateObject(SIDE_A_ID, 0);
	// delay(1000);
	// actuators.delevateObject(SIDE_A_ID, 0);
	// delay(1000);
	// actuators.delevateObject(SIDE_A_ID, 0);
	// delay(1000);
	// strategy.movement.Calibrate();
	// actuators.performTEST();
	// strategy.startStratA(false);
	// strategy.startSEMIOFFSET(false);
	// strategy.startStratA(false);
	// strategy.actuators.performTEST();
	// Serial.println("START");
	// Serial.println(lidar.hasDetected());
	// actuators.performTEST();
	// delay(5000);
	// strategy.movement.rotateTo(-60.0);
	// strategy.movement.runSync();
	// delay(5000);
	// strategy.movement.rotateTo(120.0);
	// strategy.movement.runSync();
	// strategy.startSEMIOFFSET(false);
}