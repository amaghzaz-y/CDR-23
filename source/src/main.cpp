#include <Arduino.h>
#include <types/PolarVec.h>
#include <core/Lidar.h>
#include <core/Strategy.h>
#include <lib/ticker/Ticker.h>
#include <utils/utils.h>
#include <core/Actuators.h>
#include <utils/PINS.h>
#include <core/LCD.h>

Display display;
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

Ticker ticker(FullStop,
			  100000, 0, MILLIS);

// Point2D points[] = {Point2D(1000, 500), Point2D(1000, 1000), Point2D(700, 1000)};

void LidarTask(void *pvParameters)
{
	for (;;)
	{
		lidar.Task(strategy.getCurrentPoint());
		ticker.update();
	}
}

void setup()
{
	Serial.begin(9600);
	// pinMode(15, INPUT_PULLUP);
	// pinMode(PIN_L2, INPUT_PULLUP);
	// pinMode(PIN_L3, INPUT);
	// pinMode(PIN_L4, INPUT_PULLUP);
	display.setup();
	display.Show("UniMakers", 0);
	// lidar.setup();
	// lidar.setAngle(180);
	// lidar.setRadius(360);
	// lidar.setMaxRange(350);
	strategy.setup();
	xTaskCreatePinnedToCore(LidarTask, "lidarTask", 10000, NULL, 0, NULL, 0);
}

void loop()
{
	strategy.Homologuation(lidar.hasDetected());
}