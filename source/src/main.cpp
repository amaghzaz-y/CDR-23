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

Movement movement;

PolarVec vecs[] = {PolarVec(0, 10), PolarVec(120, 10), PolarVec(240, 10)};

void simple_strat()
{
	log("start", 0);
	int i = 0;
	for (i; i < 3; i++)
	{
		log("iteration", i);
		Serial.println();
		movement.setTargetRelative(vecs[i].ToSteps());
		while (!movement.hasArrived())
		{
			// Serial.print(movement.M1.getCurrentPositionInSteps());
			// Serial.print(" - ");
			// Serial.print(movement.M2.getCurrentPositionInSteps());
			// Serial.print(" - ");
			// Serial.print(movement.M3.getCurrentPositionInSteps());
			// Serial.print("       ||  ");
			// Serial.print(movement.M1.motionComplete());
			// Serial.print(" - ");
			// Serial.print(movement.M2.motionComplete());
			// Serial.print(" - ");
			// Serial.println(movement.M3.motionComplete());
			// delay(500);
			movement.run();
		}
	}
}
Lidar lidar;

void LidarTask(void *pvParameters)
{
	lidar.Task(pvParameters);
}

void setup()
{
	Serial.begin(9600);
	// movement.setup();
	lidar.setup();
	lidar.setAngle(0);
	lidar.setRadius(180);
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
	// Serial.println("starting");
	// log("start", 0);
	// simple_strat();
	// log("finished movement", movement.hasArrived());
}