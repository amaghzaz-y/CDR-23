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

PolarVec vecs[] = {PolarVec(0, 20), PolarVec(120, 20), PolarVec(240, 20)};
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
			movement.run();
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