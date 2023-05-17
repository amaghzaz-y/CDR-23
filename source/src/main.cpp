#include <Arduino.h>
#include <types/PolarVec.h>
#include <core/Lidar.h>
#include <core/Strategy.h>
#include <lib/ticker/Ticker.h>

Strategy strategy;
Lidar lidar;

bool lidarStatus = false;
void FullStop()
{
	strategy.stop();
}

Ticker ticker(FullStop,
			  95500, 0, MILLIS);

void LidarTask(void *pvParameters)
{
	for (;;)
	{
		lidarStatus = lidar.Task(strategy.getCurrentPoint());
		ticker.update();
	}
}

void setup()
{
	Serial.begin(9600);
	lidar.setup();
	lidar.setMaxRange(320);
	lidar.setRadius(360);
	lidar.setAngle(180);
	strategy.setup();
	xTaskCreatePinnedToCore(LidarTask, "lidarTask", 10000, NULL, 0, NULL, 0);
}

void loop()
{
	// strategy.Homologuation(&lidarStatus);
	strategy.Initiation();
	strategy.Ready();
	ticker.start();
	while (1)
	{
		strategy.sensors.testSensors();
	}
	strategy.startStratA(&lidarStatus);
	// strategy.movement.lidarTest(&lidarStatus);
}