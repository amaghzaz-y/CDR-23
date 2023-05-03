#include <Arduino.h>
#include <types/PolarVec.h>
#include <core/Lidar.h>
#include <core/Strategy.h>
#include <ticker/Ticker.h>
#include <utils/utils.h>
void log(char *msg, int value)
{
	Serial.print(msg);
	Serial.print(" : ");
	Serial.println(value);
}

Strategy strategy;
Lidar lidar;

void FullStop()
{
	strategy.stop();
}

Ticker ticker(FullStop, 1200000, 1);

Point2D points[] = {Point2D(1000, 500), Point2D(1000, 1000), Point2D(700, 1000)};

void LidarTask(void *pvParameters)
{
	for (;;)
	{
		lidar.Task();
		ticker.update();
	}
}

void setup()
{
	Serial.begin(9600);
	lidar.setup();
	lidar.setAngle(180);
	lidar.setRadius(360);
	lidar.setMaxRange(300);
	strategy.setup();
	// xTaskCreatePinnedToCore(LidarTask, "lidarTask", 10000, NULL, 0, NULL, 0);
	strategy.setPoints(points, 3);
}

void loop()
{
	// delay(5000);
	// strategy.movement.rotateTo(-60.0);
	// strategy.movement.runSync();
	// delay(5000);
	// strategy.movement.rotateTo(120.0);
	// strategy.movement.runSync();
	strategy.startSEMI(false);
}