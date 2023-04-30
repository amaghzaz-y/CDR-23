#include <Arduino.h>
#include <types/PolarVec.h>
#include <core/Lidar.h>
#include <core/Strategy.h>
#include <ticker/Ticker.h>

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
	strategy.movement.stop();
}

Ticker ticker(FullStop, 120000, 1);

// PolarVec vecs[] = {PolarVec(0, 50), PolarVec(120, 50), PolarVec(240, 50)};
Point2D points[] = {Point2D(1000, 500), Point2D(500, 500), Point2D(400, 400), Point2D(343, 545)};

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
	strategy.setup();
	lidar.setup();
	lidar.setAngle(180);
	lidar.setRadius(360);
	lidar.setMaxRange(300);
	// xTaskCreatePinnedToCore(LidarTask, "lidarTask", 10000, NULL, 0, NULL, 0);
	strategy.movement.setPoints(points, 4);
	strategy.setup();
}
float rotation = 0.0;

void loop()
{
	strategy.start(false);
}
