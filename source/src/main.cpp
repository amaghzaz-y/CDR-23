#include <Arduino.h>
#include <core/Movement.h>
#include <types/PolarVec.h>

void log(char *msg, int value)
{
	Serial.print(msg);
	Serial.print(" : ");
	Serial.println(value);
}

Movement movement;

PolarVec vecs[] = {PolarVec(0, 100), PolarVec(120, 100), PolarVec(240, 100)};

void simple_strat()
{
	log("start", 0);
	int i = 0;
	for (i; i < 3; i++)
	{ 
		log("iteration", i);
		Serial.println();
		movement.setTargetRelative(vecs[i].ToSteps());
		movement.run();

		while (!movement.hasArrived())
		{
			Serial.print(movement.M1.getCurrentPositionInSteps());
			Serial.print(" - ");
			Serial.print(movement.M2.getCurrentPositionInSteps());
			Serial.print(" - ");
			Serial.print(movement.M3.getCurrentPositionInSteps());
			Serial.print("       ||  ");
			Serial.print(movement.M1.motionComplete());
			Serial.print(" - ");
			Serial.print(movement.M2.motionComplete());
			Serial.print(" - ");
			Serial.println(movement.M3.motionComplete());
			delay(1000);
		}
	}
}

void setup()
{
	Serial.begin(115200);
	movement.setup();
}

void loop()
{
	// Serial.println("starting");
	// log("start", 0);
	simple_strat();
	log("finished movement", movement.hasArrived());
}