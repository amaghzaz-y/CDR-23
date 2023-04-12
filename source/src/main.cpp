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
	strategy.stop();
}

Ticker ticker(FullStop, 120000, 1);

PolarVec vecs[] = {PolarVec(0, 50), PolarVec(120, 50), PolarVec(240, 50)};

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
	xTaskCreatePinnedToCore(LidarTask, "lidarTask", 10000, NULL, 0, NULL, 0);
	strategy.setVecs(vecs, 3);
}

void loop()
{
	while (!strategy.isReady())
	{
		strategy.makeSelection();
	}
	ticker.start();
	strategy.executeVecs(false);
}