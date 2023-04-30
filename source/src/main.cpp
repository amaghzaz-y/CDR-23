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
	strategy.setPoints(points, 4);
}
float rotation = 0.0;

void loop()
{
	// strategy.start(false);
	// while (!strategy.atHome())
	// {
	// 	strategy.init();
	// }
	// Steps steps = strategy.movement.rotateTo(-20.0);
	// strategy.movement.moveToRel(steps);
	// strategy.movement.runSync();
	// delay(2000);
	// strategy.setNextPoint(Point2D(1000, 500));
	// strategy.goToPoint();
	// strategy.setNextPoint(Point2D(1000, 1000));
	// strategy.goToPoint();
	// strategy.setNextPoint(Point2D(500, 1500));
	// strategy.goToPoint();
	// strategy.setNextPoint(Point2D(1000, 500));
	// strategy.goToPoint();
	// strategy.setNextPoint(Point2D(HOME_1_POS.X, HOME_1_POS.Y));
	// strategy.goToPoint();
	// delay(5000);
	strategy.rotateTo(Point2D(1000, 1000));
	// delay(2000);
	strategy.rotateTo(Point2D(500, 1000));
	// delay(2000);
	// strategy.rotateTo(Point2D(1000, 500));
	// delay(2000);
	// Steps steps = strategy.movement.rotateTo(-60.0 - rotation);
	// strategy.movement.moveToRel(steps);
	// strategy.movement.runSync();
	// rotation = -60.0;
	// delay(2000);
	// steps = strategy.movement.rotateTo(60 - rotation);
	// strategy.movement.moveToRel(steps);
	// strategy.movement.runSync();
	// rotation = 60;
}
