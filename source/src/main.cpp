#include <Arduino.h>
#include <core/Movement.h>
#include <types/PolarVec.h>
#include <core/Lidar.h>
void log(char *msg, int value)
{
	Serial.print(msg);
	Serial.print(" : ");
	Serial.println(value);
}
Lidar lidar;

Movement movement;

PolarVec vecs[] = {PolarVec(0, 30), PolarVec(120, 30), PolarVec(240, 30)};
// Point2D points[] = {Point2D(0, 0), Point2D(0, 10), Point2D(50, 10), Point2D(10, 0), Point2D(0, 0)};

// void simple_strat()
// {
// 	log("start", 0);
// 	int i = 0;
// 	for (i; i < 5; i++)
// 	{
// 		log("iteration", i);
// 		Serial.println();
// 		movement.setTargetRelative(points[i].toSteps());
// 		while (!movement.hasArrived())
// 		{
// 			// if (lidar.hasDetected())
// 			// {
// 			// 	movement.stop();
// 			// }
// 			movement.run();
// 		}
// 	}
// }

void LidarTask(void *pvParameters)
{
	lidar.Task(pvParameters);
}

void setup()
{
	Serial.begin(9600);
	movement.setup();
	lidar.setup();
	lidar.setAngle(180);
	lidar.setRadius(360);
	lidar.setMaxRange(300);
	xTaskCreatePinnedToCore(
		LidarTask,	 /* Function to implement the task */
		"lidarTask", /* Name of the task */
		10000,		 /* Stack size in words */
		NULL,		 /* Task input parameter */
		0,			 /* Priority of the task */
		NULL,		 /* Task handle. */
		0);
}

void loop()
{
	// Serial.print("detected ->     ");
	// Serial.println(lidar.hasDetected());
	Serial.println("starting");
	log("start", 0);
	// simple_strat();
	movement.moveTo(PolarVec(120.0, (50.0 * 1.025)).ToStepsCosSin()); //* 1.037
	while (!movement.hasArrived())
	{
		movement.run();
	}
	delay(5000);
	log("finished movement", movement.hasArrived());
}